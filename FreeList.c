#include "FreeList.h"

FreeListP newFreeList(size_t maxSize){
  FreeListP freeList = malloc(sizeof(FreeList));
  InfoP infoHead = malloc(sizeof(Info));
  infoHead->size = maxSize;
  freeList->head = newListNode(infoHead, NULL);
  return freeList;
}


void destroyFreeList(FreeListP freeListP){
  free(freeListP);
}


size_t allocateFirstFitFreeList(FreeListP this, size_t allocSize){
 size_t firstFitpos = -1;
 ListNodeP currentFirst = this->head;
 ListNodeP previousFirst;
 while(currentFirst != NULL){
  //Checks for first Free node with enough space
  if((currentFirst->info->size)>=allocSize){
   firstFitpos = currentFirst->info->pos;
   currentFirst->info->size -= allocSize;
   currentFirst->info->pos += allocSize;

    //If node gets filled, remove it
    if(currentFirst->info->size == 0){
      if(firstFitpos <= this->head->info->pos){
	this->head = this->head->next;
      }
      else{
      previousFirst->next = currentFirst->next;
     }
	destroyFreeListNode(currentFirst);
    }
   return firstFitpos;
  }
  previousFirst = currentFirst;
  currentFirst = currentFirst->next;
 }
 return -1;
}



size_t allocateBestFitFreeList(FreeListP this, size_t allocSize){
 ListNodeP currentBest = this->head;
 size_t bigNum = 999999;
 size_t smallest = bigNum;
 while(currentBest != NULL){
  //Checks for SMALLEST Free node with enough space
  if( ((currentBest->info->size)<smallest) && ((currentBest->info->size)>=allocSize) ){
    smallest = currentBest->info->size;
  }
   currentBest = currentBest->next;
 }

  //If none found, just end
  if(smallest >= bigNum)  return -1;
  //Else
  size_t BestFitpos = -1;
  ListNodeP previousBest;
  currentBest = this->head;

  while(currentBest != NULL){
  //Re-Finds the node with the saved space
  if((currentBest->info->size)==smallest){
   currentBest->info->size -= allocSize;
   BestFitpos = currentBest->info->pos;
   currentBest->info->pos += allocSize;

    //If node gets filled, remove it
    if(currentBest->info->size == 0){
      if(BestFitpos <= this->head->info->pos){
	this->head = this->head->next;
      }
      else{
      previousBest->next = currentBest->next;
     }
	destroyFreeListNode(currentBest);
    }
   return BestFitpos;
  }
  previousBest = currentBest;
  currentBest = currentBest->next;
 }

 return BestFitpos;
}




size_t allocWorstFitFreeList(FreeListP this, size_t allocSize){
 ListNodeP currentWorst = this->head;
 size_t largest = 0;
 while(currentWorst != NULL){
   if((currentWorst->info->size)>largest){
   largest = currentWorst->info->size;
  }
  currentWorst = currentWorst->next;
 }

 //If not possible to fit
 if (largest <= allocSize) return -1;

 //Else
 size_t WorstFitpos = -1;
 ListNodeP previousWorst;
 currentWorst = this->head;

 while(currentWorst != NULL){
  //Re-Finds the node with the saved space
  if((currentWorst->info->size)==largest){

   currentWorst->info->size -= allocSize;
   WorstFitpos = currentWorst->info->pos;
   currentWorst->info->pos += allocSize;

    //If node gets filled, remove it
    if(currentWorst->info->size == 0){
      if(WorstFitpos <= this->head->info->pos){
	this->head = this->head->next;
      }
      else{
      previousWorst->next = currentWorst->next;
     }
	destroyFreeListNode(currentWorst);
    }
   return WorstFitpos;
  }
  previousWorst = currentWorst;
  currentWorst = currentWorst->next;
 }
 return WorstFitpos;
}




//This is called when a node is removed from allocList
size_t deallocateFreeList(FreeListP this, size_t allocPos, size_t allocSize){
 //If node removed BEFORE head of freeList
 if(allocPos< (this->head->info->pos)){
  //If removing item touching head, merge
  if(allocPos+allocSize+1 >= this->head->info->pos){
    this->head->info->pos = allocPos;
    this->head->info->size += allocSize;
   }
  else{
   InfoP infoDeallocateFree = malloc(sizeof(Info));
   infoDeallocateFree->pos = allocPos;
   infoDeallocateFree->size = allocSize;
   InfoP infoDeAllocNode = malloc(sizeof(Info));
   infoDeAllocNode->pos = allocPos;
   infoDeAllocNode->size = allocSize;
   ListNodeP newDeallocate = newListNode(infoDeallocateFree, this->head);
   this->head = newDeallocate;
  }
  return allocPos;
 }
 //If node removed AFTER head of freeList
  ListNodeP beforeDealloc = this->head;
  ListNodeP afterDealloc = beforeDealloc->next;
  while((beforeDealloc->next != NULL) && ((afterDealloc->info->pos) < allocPos)){
   beforeDealloc = afterDealloc;
   afterDealloc = afterDealloc->next;
  }
  if(afterDealloc != NULL){
  //If merging before+after
  if( ((beforeDealloc->info->pos)+(beforeDealloc->info->size)+1 >= allocPos) 
  && ((afterDealloc->info->pos) <= allocPos+allocSize+1) ){
   (beforeDealloc->info->size) += (allocSize + ( afterDealloc->info->size));
   beforeDealloc->next = afterDealloc->next;
   destroyFreeListNode(afterDealloc);
   return allocPos;
   }
   //If merging only with after
   if((afterDealloc->info->pos) <= allocPos+allocSize+1){
   afterDealloc->info->size = allocPos;
   afterDealloc->info->size += allocSize;
   return allocPos;
   }
  }
  //If merging only with before
  if((beforeDealloc->info->pos)+(beforeDealloc->info->size)+1 >= allocPos){
  beforeDealloc->info->size += allocSize;
  return allocPos;
  }
  //If not merging
  InfoP infoDeallocateFree = malloc(sizeof(Info));
  infoDeallocateFree->pos = allocPos;
  infoDeallocateFree->size = allocSize;
  ListNodeP newDeallocate = newListNode(infoDeallocateFree, afterDealloc);
  beforeDealloc->next = newDeallocate;   
  return allocPos;
}



size_t countFreeHoles(FreeListP this){
 ListNodeP currentCount = this->head;

 if(currentCount == NULL){
	return 0;
	}

 size_t freeCount = 1;
 while(currentCount->next !=NULL){
  currentCount = currentCount->next;
  freeCount ++;
  }
 return freeCount;
}
