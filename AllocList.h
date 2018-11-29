#ifndef ALLOCLIST_H
#define ALLOCLIST_H
#include "ListNode.h"

//This contains pointers to Allocated spaces, taking each "task" separately.

typedef struct AllocList* AllocListP;

typedef struct AllocList{
ListNodeP head;
}AllocList;

AllocListP newAllocList();
void destroyAllocList(AllocListP this);
size_t addAllocList(AllocListP this, size_t allocPos, size_t allocSize);
size_t removeAllocList(AllocListP this, size_t allocPos);
size_t countAllocChunks(AllocListP this);

#endif
