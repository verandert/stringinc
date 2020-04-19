#ifndef _IDXLIST_H
#define _IDXLIST_H

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int elemtype;
//链表堆分配表示
typedef struct LNode
{
    elemtype data;
    struct LNode *next;
}LNode, *LinkList;

//串堆分配表示
typedef struct
{
    char *base;
    int length;
}HString;

//串相关函数的声明
void StrAssign(HString *S, char *p);
void StrInsert(HString *S, int pos, HString T);
int CompareStr(HString S, HString T);
void SubString(HString S, HString *T, int pos, int len);
void DelSubString(HString *S, int pos, int len);
void Replace(HString *S, HString T, HString V, int next[]);
int MatchByKmp(HString S, HString T, int pos, int next[]);
void GetNext(HString S, int next[]);

//链表相关函数的声明
void InitList(LinkList head);
elemtype GetElem(LinkList head, int i);
elemtype DeleteList(LinkList head, int i);
void InsertList(LinkList head, int i, elemtype data);
bool IsListEmpty(LinkList head);
void append(LinkList head, elemtype data);

#endif