#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *base;
    int length;
}HString;

void StrAssign(HString *S, char *p);
void StrInsert(HString *S, int pos, HString T);
int CompareStr(HString S, HString T);
void SubString(HString S, HString *T, int pos, int len);
void DelSubString(HString *S, int pos, int len);
void Replace(HString *S, HString T, HString V, int next[]);
int MatchByKmp(HString S, HString T, int pos, int next[]);
void GetNext(HString S, int next[]);

// int main()
// {
//     HString S = {NULL, 0}, T = {NULL, 0}, V = {NULL, 0};
//     StrAssign(&S, "archlinux");
//     StrAssign(&T, "arch");
//     int next[T.length + 1];
//     printf("%d\n", MatchByKmp(S, T, 1, next));
//     StrAssign(&V, "manjaro");
//     Replace(&S, T, V, next);
//     printf("%s", S.base);
//     printf("\n");
//     return 0;
// }

//初始化一个串
void StrAssign(HString *S, char *p)
{
    int len = 0;
    char *q = p;
    while (*q++) ++len;
    if(!len) {S->base = NULL; S->length = 0;}
    else
    {
        S->base = (char *)malloc((len+1)*sizeof(char));
        if(!S->base) {printf("内存分配失败"); exit(-1);}
        S->length = len;
        for (int i = 0; i < len; i++)
        {
            S->base[i] = p[i];
        }
        S->base[len] = '\0';
    }
}

//在窜S指定位置插入窜T
void StrInsert(HString *S, int pos, HString T)
{
    int n, m;
    if(pos < 1 || pos > S->length+1) {printf("插入位置错误"); exit(-1);}
    if(T.length)
    {
        m = S->length; n = T.length;
        S->base = (char *)realloc(S->base, (m+n+1)*sizeof(char));
        if(!S->base) {printf("内存分配失败"); exit(-1);}
        for (int i = m - 1; i >= pos - 1; i--)
        {
            S->base[i + T.length] = S->base[i];
        }
        for (int i = 0; i < T.length; i++)
        {
            S->base[pos-1+i] = T.base[i];
        }
        S->length = m+n;
        S->base[m+n] = '\0';
    }
}

//比较串S和T, >=<分别返回>0,0,<0;
int CompareStr(HString S, HString T)
{
    int i = 0;
    while (S.base[i] && T.base[i])
    {
        if(S.base[i] != T.base[i]) return S.base[i] - T.base[i];
        i++;
    }
    return S.length - T.length;
}

//清空串
void ClearString(HString *S)
{
    if(S->base) 
    {
        free(S->base); S->base = NULL; 
    }
    S->length = 0;
}
//删除子串S[pos-1...pos+len-2]
void DelSubString(HString *S, int pos, int len)
{
    int i, j;
    if(pos < 1 || pos > S->length || len < 1 || len > S->length - pos + 1)
    {
        printf("不存在该子串"); exit(-1);
    }
    for (i = 0, j = pos - 1 + len; j < S->length; i++, j++)
    {
        S->base[pos-1+i] = S->base[j];
    }
    S->base[pos-1+i] = '\0';
    S->length = S->length - len;
    //S->base = (char *)realloc(S->base, S->length*sizeof(char));
    if(!(S->base = (char *)realloc(S->base, S->length*sizeof(char)))) {printf("内存分配失败"); exit(-1);}
}
//取串S中的子串S[pos-1...pos+len-2];
void SubString(HString S, HString *T, int pos, int len)
{
    if(pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1 )
    {printf("不存在该子串"); exit(-1);}
    if(T->base) {free(T->base); T->base = NULL;}
    if((T->base = (char *)malloc((len+1)*sizeof(char))))
    {
        for (int i = 0; i < len; i++)
        {
            T->base[i] = S.base[pos-1+i];   
        }
        T->base[len] = '\0';
        T->length = len;
    }
    else {printf("内存分配失败"); exit(-1);}
}

//用串V取代串S中的不重叠非空串T
void Replace(HString *S, HString T, HString V, int next[])
{
    int i = 1, pos;
    while (i <= S->length - T.length + 1)
    {
        pos = MatchByKmp(*S, T, i ,next);
        if(pos){
            DelSubString(S, pos, T.length);
            StrInsert(S, pos, V);
            i = pos + V.length + 1;
        }
        else break; //未能找到匹配的子串
    }  
}
//KMP模式匹配算法
void GetNext(HString S, int next[])
{
    int i = 1, j = 0;
    next[0] = 0;
    next[1] = 0;
    while (i < S.length)
    {
        if(j == 0 || S.base[i - 1] == S.base[j - 1]) {
            ++i; ++j;
            if(S.base[i - 1] != S.base[j - 1]) next[i] = j;
            else next[i] = next[j];
        }
        else j = next[j];
    }
}

int MatchByKmp(HString S, HString T, int pos, int next[])
{
    GetNext(T, next);
    int i = pos, j=1;
    while (j <= T.length && i <= S.length)
    {
        if(j == 0 || S.base[i - 1] == T.base[j - 1])
        {
            i++; j++;
        }
        else j = next[j];
    }
    if(j > T.length) return (i - T.length);
    return 0;
}
