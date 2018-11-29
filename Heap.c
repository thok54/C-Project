#include "Heap.h"

HeapP newHeap(size_t heapSize, size_t allocMode){
 HeapP heap = malloc(sizeof(Heap));
  heap->usedSize = 0;
  heap->freeSize = heapSize;
  heap->allocMode = allocMode;
  heap->freeList = newFreeList(heapSize);
  heap->allocList = newAllocList();
  //This points to actual heap
  heap->heapBuffer = malloc(heapSize);

 return heap;
}

//void* is real world pointer. Convert to size_t heapPosition"
//void* = malloc+pos
//pos = void* - malloc


void destroyHeap(HeapP this){
 destroyFreeList(this->freeList);
 destroyAllocList(this->allocList);
 free(this);
}

//Check space in free list. If possible, allocate node to both lists
void* allocateHeap(HeapP this, size_t allocSize){
 size_t allocPosition;
 if(this->allocMode == FIRST){
   allocPosition = allocateFirstFitFreeList(this->freeList, allocSize);
  }
 else if(this->allocMode == BEST){
   allocPosition = allocateBestFitFreeList(this->freeList, allocSize);
  }
 else if(this->allocMode == WORST){
   allocPosition = allocWorstFitFreeList(this->freeList, allocSize);
  }
 if(allocPosition == -1){
  printf("Can't allocate");
  printf("\n");
  return (allocPosition+ (char*)(this->heapBuffer));
 }
 addAllocList(this->allocList, allocPosition, allocSize);
 this->usedSize +=  allocSize;
 this->freeSize -=  allocSize;
 return (allocPosition+ (char*)(this->heapBuffer));
}


size_t deallocateHeap(HeapP this, void* p){
 size_t deallocPos = p-(this->heapBuffer);
 size_t deallocSize = removeAllocList(this->allocList, deallocPos);
 if(deallocSize == -1){
  printf("Can't deallocate");
  printf("\n");
  return deallocPos;
 }
 deallocateFreeList(this->freeList, deallocPos, deallocSize);

 this->usedSize -=  deallocSize;
 this->freeSize +=  deallocSize;
 return deallocPos;
}


//Stats: Heap used ratio, number of free holes, Avg size of holes, Number of allocated chunks.
void heapStats(HeapP this){
 printf("Heap used ratio = ");
 printf("%zu", (((this->usedSize)*100) / ((this->freeSize)+(this-> usedSize))));
 printf("%%");
 printf("\n");
 
 printf("Number of free holes = ");
 printf("%zu", countFreeHoles(this->freeList));
 printf("\n");

 printf("Average size of holes = ");
 if(countFreeHoles(this->freeList) == 0) printf("%i",0);
 else printf("%zu", (this->freeSize)/countFreeHoles(this->freeList));
 printf("\n");

 printf("Number of allocated chunks = ");
 printf("%zu", countAllocChunks(this->allocList));
 printf("\n");
}
