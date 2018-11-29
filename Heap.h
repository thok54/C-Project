#ifndef HEAP_H
#define HEAP_H
#include "FreeList.h"
#include "AllocList.h"

//This contains pointers to both lists

typedef struct Heap *HeapP;

typedef enum {
  FIRST = 1,
  BEST = 2,
  WORST = 3,
  }ALLOCMODE;

typedef struct Heap{
FreeListP freeList;
AllocListP allocList;
void* heapBuffer;
size_t usedSize;
size_t freeSize;
ALLOCMODE allocMode;
}Heap;


HeapP newHeap(size_t heapSize, size_t allocMode);
void destroyHeap(HeapP this);
void* allocateHeap(HeapP this, size_t allocSize);
size_t deallocateHeap(HeapP this, void* p);

//Stats: Heap used ratio, number of free holes, Avg size of holes, Number of allocated chunks.
void heapStats(HeapP this);

#endif
