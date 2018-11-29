#ifndef LISTNODE_H
#define LISTNODE_H

#include "Info.h"
#include <stdio.h>

typedef struct ListNode *ListNodeP;

typedef struct ListNode{
 InfoP info;
 ListNodeP next;
}ListNode;

ListNodeP newListNode(InfoP info, ListNodeP next);

void destroyFreeListNode(ListNodeP freeListNode);

#endif
