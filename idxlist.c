#include "./idxlist.h"

#define MaxWordNum 10//关键词词表长度
#define MaxKeyNum 2500//索引表长度
#define MaxLineNUM 500//书目每行最大字符数

//常用词表
typedef struct
{
    char *item[MaxWordNum];
    int len;
}WordList;

//词索引表数据
typedef struct
{
    HString S;
    LinkList link;
}IdxType;

//索引表
typedef struct
{
    IdxType idxitem[MaxKeyNum]; 
    int length;
}IdxList;

void GetLine(FILE *f, char str[], char c);
int CompareS(char *S, char *T);
void ExtractKeyWord(char str[], char *frequent[], WordList *wdl);
int Aoti(char *p);
int BinarySearch(IdxList *idxlist, int low, int high, char *target, int *flag);
void InsertIdxList(IdxList *idxlist, WordList *wdlist);

int main(){
    char *frequentword[] = {"to", "on", "the", "of", "an", "a", "i", "am"};//常用词数组
    FILE *f = NULL;
    char ch;
    WordList wdlist;
    LinkList p;
    char str[MaxLineNUM+1];
    IdxList idxlist;
    idxlist.length = 0;
    if((f=fopen("./test.txt", "r"))){
        ch = fgetc(f);
        while(!feof(f)){
            GetLine(f, str, ch);
            ch = fgetc(f);
            ExtractKeyWord(str, frequentword, &wdlist);
            // printf("%d\n", Aoti(wdlist.item[0]));
            // for (int i = 1; i < wdlist.len; i++)
            // {
            //     printf("%s\n", wdlist.item[i]);
            // }
            // printf("-------分割线------\n");
            InsertIdxList(&idxlist, &wdlist);
        }
        fclose(f);
        f = NULL;
    }
    for (int i = 0; i <= idxlist.length - 1; i++)
    {
        p = idxlist.idxitem[i].link->next;
        printf("%s:", idxlist.idxitem[i].S.base);
        while (p)
        {
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }
    return 0;
}
//逐行读入，空格用一个空操作符代替；结尾加两个空操作符；
void GetLine(FILE *f, char str[], char c) {
    char ch, *p, temp;
    ch = c;
    p = str;
    while(ch != '\n' && ch != EOF)
    {
        temp = ch;
        ch = fgetc(f);
        if(temp == 32 && ch == 32) *p = '\0';
        else if(temp == 32 && ch != 32) *p++ = '\0';
        else *p++ = temp;
    }
    *p = '\0';
    *(p+1) = '\0';
}
//提取关键词，去掉常用词。
void ExtractKeyWord(char s[], char *frequent[], WordList *wdl){
    int i = 0, j;
    wdl->item[i] = s;//书号存在第一个位置
    while (*s || *(s+1))
    {
        if(*s == '\0'){
            for (j = 0; j < 8; j++)
            {
                if(CompareS(s+1, frequent[j]) == 0) break;
            }
            if(j >= 8) wdl->item[++i] = s + 1;//不属于常用词则插入关键词表wdlist中
        }
        s++;
    }
    wdl->len = i + 1; 
}

//比较两个字符串， >=< 分别返回>0, 0, <0;
int CompareS(char *S, char *T){
    while (*S && *T)
    {
        if(*S != *T) return (*S - *T);
        S++; T++;
    }
    return *S - *T;
}

//串转化为整数
int Aoti(char *p){
    int value = 0;
    while (*p)
    {
       value = value * 10 + *p++ - '0';
    }
    return value;
}

//折半查找
int BinarySearch(IdxList *idxlist, int low, int high, char *target, int *flag){
    int mid = 0;
    while (low <= high)
    {   
        mid = (low + high) / 2;
        if(CompareS(target, idxlist->idxitem[mid].S.base) > 0) low = mid + 1;//if内还是用表达式好点
        else if(CompareS(idxlist->idxitem[mid].S.base, target) > 0) high = mid - 1;
        else return mid;
    }
    *flag = low;
    return -1;
}

void InsertIdxList(IdxList *idxlist, WordList *wdlist) {
    int flag;//
    int index;//找不到返回-1， 找到返回该位置；
    for (int i = 1; i < wdlist->len; i++)
    {
        index = BinarySearch(idxlist, 0, idxlist->length - 1, wdlist->item[i], &flag);
        if(index != -1){
            append(idxlist->idxitem[index].link, Aoti(wdlist->item[0]));
        }//查找的到直接插入新书号
        else
        {
            for (int i = idxlist->length - 1; i >= flag; i--)
            {
                idxlist->idxitem[i + 1] = idxlist->idxitem[i];
            }
            IdxType idx;//不会重复分配内存
            idx.link = (LinkList)malloc(sizeof(LNode));
            idx.link->next = NULL;
            idx.link->data = 0;
            StrAssign(&idx.S, wdlist->item[i]);
            idxlist->idxitem[flag] = idx;
            append(idxlist->idxitem[flag].link, Aoti(wdlist->item[0]));
            idxlist->length++; 
        }//查找不到则索引表插入新关键词， 并插入书号
    }
    
}
