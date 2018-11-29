#include "ListNode.h"

ListNodeP newListNode(InfoP info, ListNodeP next){
  ListNodeP listNode = malloc(sizeof(ListNode));
  listNode->info = info;
  listNode->next = next;
  return listNode;
}

void destroyFreeListNode(ListNodeP freeListNode){
  free(freeListNode->info);
  free(freeListNode);
}
