#include "Heap.h"
#include <string.h>

int main(int argc, char *argv[]){

//Get heap Size
size_t heapSize = 0;
sscanf(argv[1], "%zu", &heapSize);

//Set heap Mode
ALLOCMODE heapMode = 0;
char algorithm[6];
sscanf(argv[2], "%s", algorithm);

if (strcmp(algorithm, "first") == 0){
 heapMode = FIRST;
};
if (strcmp(algorithm, "best") == 0){
 heapMode = BEST;
};
if (strcmp(algorithm, "worst") == 0){
 heapMode = WORST;
};

//Initialize heap
HeapP heap = newHeap(heapSize, heapMode);



//Array of 10,000 char* to strings
//Array Stores positions in heap, which point to the string allocated
int arrSize = 10000;
char* strings[arrSize];
//For some reason string has crap on it by default, so have to clear it first.
memset(strings, 0, arrSize * (sizeof strings[0]));  

FILE *fp;






//WHEN RUNNING THE PROGRAM, COMMENT OUT WHICH FILE YOU WANT TO USE, WHILE HIDING THE ONES YOU DON'T
//fp = fopen("traceSmall.txt", "r"); 
//fp = fopen("traceMedium.txt", "r");
fp = fopen("traceLarge.txt", "r");  





    
char in[1000];
size_t stringSize; 
int i = 0;  


//Stores file lines into array
while (fgets(in, sizeof in, fp) != NULL) {

    stringSize = strlen(in+2);
    in[stringSize-1] = '\0';

    //If +, try to add
    if(in[0]=='+'){
	printf("Adding ");
	for(i =0; i<arrSize;i++){		
	if(strings[i] == NULL){				
		strings[i] = (char*)allocateHeap(heap, stringSize);
		//Goes to memory void*, and writes string there
		strcpy(strings[i], in+2);
		printf("%s\n", strings[i]);
		break;
		}
	  }
	}
    
    //If -, try to delete
   else if(in[0]=='-'){
	printf("\n");
	printf("\n");
	printf("Trying to Delete\n");
        printf("%s\n",in+2);
	for (i = 0;i<5;i++){
	if(strings[i] != NULL){
	   if(strcmp((in+2), strings[i]) == 0){
		printf("Deleted string strings[%i] is %s\n",i, strings[i]);
		deallocateHeap(heap, strings[i]);
		strings[i] = NULL;
		break;	
	   }
	  }
	 }
      }
}


heapStats(heap);
destroyHeap(heap);
return 0;
}
