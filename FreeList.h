#ifndef FREELIST_H
#define FREELIST_H

#include "ListNode.h"

//Index. List is stored in buffer
//This points to free spaces

typedef struct FreeList* FreeListP;

typedef struct FreeList{
ListNodeP head;
}FreeList;

FreeListP newFreeList(size_t maxSize);
void destroyFreeList(FreeListP freeListP);
size_t allocateFirstFitFreeList(FreeListP this, size_t allocSize);
size_t allocateBestFitFreeList(FreeListP this, size_t allocSize);
size_t allocWorstFitFreeList(FreeListP this, size_t allocSize);
size_t deallocateFreeList(FreeListP this, size_t allocPos, size_t allocSize);
size_t countFreeHoles(FreeListP this);

#endif
