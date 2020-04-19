#include "./idxlist.h"

// int main(){
//     LNode L;
//     LinkList p;
//     InitList(&L);
//     append(&L, 001);
//     p = L.next;
//     while (p)
//     {
//         printf("%d", p->data);
//         p = p->next;
//     }
//     printf("\n");
//     return 0;
// }

//初始化单向链表
void InitList(LinkList head)
{
    head->next = NULL;
}
//返回第i个链表节点,不存在则exit;
elemtype GetElem(LinkList head, int i)
{
    LinkList p;
    elemtype data;
    p = head->next;
    while (p && i > 1)
    {
        p = p->next;
        i--;
    }
    if (!p || i < 1) { printf("不存在该节点"); exit(-1); }
    return data = p->data;
}

//删除第i个链表节点, 不存在则exit;
elemtype DeleteList(LinkList head, int i)
{
    LinkList p, q;
    elemtype data;  
    p = head;
    while (p->next && i > 1)
    {
        p = p->next;
        i--;
    }
    if (!(p->next) || i < 1) {printf("不存在该节点\n"); exit(-1);}
    q = p->next;
    p->next = q->next;
    data = q->data;
    free(q);
    p = head->next;
    return data;
}
//在链表第i个位置插入节点
void InsertList(LinkList head, int i, elemtype data)
{
    LinkList p, q;
    p = head;
    while (p && i > 1)
    {
        p = p->next;
        --i;
    }
    if (!p || i < 1) {printf("不存在该节点"); exit(-1);}
    q = (LinkList)malloc(sizeof(LNode));
    q->data = data;
    q->next = p->next;
    p->next = q;
}

//链表尾部追加元素
void append(LinkList head, elemtype data){
    LinkList p, q;
    p = head;
    while (p->next)
    {
        p = p->next;
    }
    if(q = (LinkList)malloc(sizeof(LNode))) {
        q->next = p->next;
        p->next = q;
        q->data = data;
    }
    else {printf("内存分配失败"); exit(-1);}
}

//融合两个非递减集合;
/*void MergeList(LinkList head, LinkList head1)
{
    LinkList La, Lb, Lc;
    La = head->next; Lb = head1->next;
    Lc = head;
    while (La && Lb)
    {
        if (La->data <= Lb->data) {Lc->next = La; Lc = La; La = La->next;}
        else {Lc->next = Lb; Lc = Lb; Lb = Lb->next;}
    }
    Lc->next = La?La:Lb;
    free(head1);
}*/

//队列是否为空
bool IsListEmpty(LinkList head)
{
    if(!head->next) return true;
    return false;
}