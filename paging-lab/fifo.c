#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

float fifo(int numFrames, int inputArray[], int size, int programFlag){
	int q[numFrames];
	int last = -1;
	int numMiss = 0;
	int numHits = 0;
	int numElements = 0;
	int numRefs = 0;
	
	//initially set to page fault, will be raised if hit
	int hitFlag = 0; 
	
	int i;
	
	for (i = 0; i < size; i++){
		//get the page from the array
		int x = inputArray[i];
		
		//reset flag for every new element
		hitFlag = 0;
		
		//case 1: page frame is full
		if(numElements == numFrames){
			numRefs++;
			//check if page hit  
			int j;
			for (j = 0; j < numFrames; j++) {
				if (q[j] == x) {
					numHits++;
					hitFlag = 1; //raise hit flag
					if(programFlag == 0){
						formatPrint(q, hitFlag, x, numFrames, numElements);
				}
					break;
				}//end if
			}//end for
			
			//if page fault
			if (hitFlag == 0){
				//evict the first page 
				numMiss++;
				last = (last + 1)%numFrames;
				q[last] = x;
				if (programFlag == 0){ 
					formatPrint(q, hitFlag, x, numFrames, numElements);
				}
			}//end if
		}
		
		
		//case 2: page frame not full
		else { 
			
			//only add if x is not in the array
			int flag = 0;
			int k;
			for (k = 0; k < numElements; k++){
				if (q[k] == x) {
					flag = 1;
					hitFlag = 1;
					if(programFlag == 0){
						formatPrint(q, hitFlag, x, numFrames, numElements);	
					}
					break;

				}
				
			}
			
			
			if (flag == 0) {
			
			q[numElements] = x;
			numElements++;
			//reset hitFlag to 1 so page fault won't be printed
			hitFlag = 1;
			if(programFlag == 0){
				formatPrint(q, hitFlag, x, numFrames, numElements);	
			}	
			}
		}//end if 
		

	}//end for
	
	
	float total = 0;
	
	if (numMiss != 0) {
		total = ((numMiss*1.0)/numRefs)*100;
		if(programFlag == 0){
			printf("Miss rate = %d / %d = %.2f%%\n",numMiss, numRefs, total);
		}
		if(programFlag == 1){
			printf("FIFO, %2d frames: Miss rate = %d / %d = %0.2f%%\n",numFrames, numMiss, numRefs, total);

		}
	}
	else {
		if(programFlag == 0){
			printf("Miss rate = %d /n", 0);
		}
		if(programFlag == 1){
			printf("FIFO, %2d frames: Miss rate = %d\n",numFrames, 0);

		}
	}
	
	return total; 
		
}//end_fifo
