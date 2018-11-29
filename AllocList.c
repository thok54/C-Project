#include "AllocList.h"

AllocListP newAllocList(){
 AllocListP allocList = malloc(sizeof(AllocList));
 InfoP infoHead = malloc(sizeof(Info));
 allocList->head = newListNode(infoHead, NULL);
 return allocList;
}

void destroyAllocList(AllocListP this){
  free(this);
}


size_t addAllocList(AllocListP this, size_t allocPos, size_t allocSize){
  //Creates info and adds it to new node
  if(allocSize == -1) return -1;
  InfoP infoAllocNode = malloc(sizeof(Info));
  infoAllocNode->pos = allocPos;
  infoAllocNode->size = allocSize;
  ListNodeP allocNode = newListNode(infoAllocNode, NULL);
  ListNodeP currentAdd = this->head;

  //If head null, adds node to head
  if(currentAdd->info == NULL){
	this->head = allocNode;
	return 0;
	}
  //Else goes to next nude, until next is null
  else{
    while(currentAdd->next != NULL){
	  currentAdd = currentAdd->next;
    }
    currentAdd->next = allocNode;
    return allocPos;
  }
}


size_t removeAllocList(AllocListP this, size_t allocPos){
   size_t currentRemoveSize;
 //Removes nodes by setting node.next to nextNode.next
 if(allocPos == 0){
  currentRemoveSize = this->head->info->size;
  destroyFreeListNode(this->head);
  this->head = this->head->next;
  return currentRemoveSize;
 }
  ListNodeP previousRemove = this->head;
  ListNodeP currentRemove = previousRemove->next;
  while((currentRemove->next) !=NULL && (currentRemove->info->pos)<allocPos){
   previousRemove = currentRemove;
   currentRemove = previousRemove->next;
  }
   if ((currentRemove->info->pos) != allocPos) return -1;

   currentRemoveSize = currentRemove->info->size;
   previousRemove->next = currentRemove->next;
   destroyFreeListNode(currentRemove);

   //RETURNS SIZE
   return currentRemoveSize;
}


size_t countAllocChunks(AllocListP this){
 ListNodeP currentCount = this->head;

 if(currentCount->info == NULL){
	return 0;
	}

 size_t allocCount = 1;
 while(currentCount->next !=NULL){
  currentCount = currentCount->next;
  allocCount ++;
  }
 return allocCount;
}
