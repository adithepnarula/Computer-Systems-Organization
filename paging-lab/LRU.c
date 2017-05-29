#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


float LRU(int numFrames, int inputArray[], int size, int programFlag){

	//create age count array
	int ageCount[numFrames];
	int aCounter;
	for (aCounter = 0; aCounter < numFrames; aCounter++){
		ageCount[aCounter] = 0;
	}//end for
	
	//create physical memory array, initlialize to -1 
	int physicalArray[numFrames];
	int pCounter;
	for(pCounter = 0; pCounter < numFrames; pCounter++){
		physicalArray[pCounter] = -1;
	}//end for 
	
	//count the number of elements
	int numElements = 0;
	
	//count the number of misses
	int numMiss = 0;
	
	//count the number of references
	int numRef = 0;
	
	//flag will switch to 1 once array is full
	int arrayFullFlag = 0;
	
	//set hitFlag to 0
	int hitFlag = 0;
	
	//loop through all elements in the local array of page references
	int i;
	for (i = 0; i < size; i++){
		//get the next page from array
		int page = inputArray[i];
		
		//reset hit flag to page fault
		hitFlag = 0;
		
		//if my arrayFullFlag is not raised, check if array is full
		if (arrayFullFlag == 0){
			int subFlag = 0;
			int sCounter;
			for(sCounter = 0; sCounter < numFrames; sCounter++){
				//if array is not full yet, raise subflag
				if(physicalArray[sCounter] == -1) {
					subFlag = 1;
					break;
				}
			}//end for 
			
			//once array FullFlag is raised, go to case 2, otherwise case 1
			if (subFlag == 0) {
				arrayFullFlag = 1;
			}
		}
		
		//case 1: physial page frames is not full
		if (arrayFullFlag == 0) {
			
			//check if the reference page is already in array
			int inFlag = 0;
			int iCounter;
			for (iCounter = 0; iCounter < numFrames; iCounter++){
				//if page in array, raise inFlag
				if (physicalArray[iCounter] == page) {
					inFlag = 1;
					break;
				}
			}//end for
			
			//case 1a: reference page is not in the array
			if (inFlag == 0) {
				
				//step1: add the element in the array
				physicalArray[numElements] = page;
				
				//step2: increase age of every element
				int ageCounter;
				for (ageCounter = 0; ageCounter < numFrames; ageCounter++){
					ageCount[ageCounter] = ageCount[ageCounter] + 1;
				}//end for 
				
				//step3: reset age of recently added page to 0
				ageCount[numElements] = 0; 
				
				//step4: add the number of elements
				numElements++;
				
				//step 5: make hitFlag page hit
				hitFlag = 1;
				
				//step6: print
				if(programFlag == 0) {
					formatPrint(physicalArray, hitFlag, page, numFrames, numElements);
				}
				
				 
				
				
			}
			
			//case 1b: reference page is already in the array
			if (inFlag == 1){
				
				
				//step1: increase age of every element
				int ageCounter;
				for (ageCounter = 0; ageCounter < numFrames; ageCounter++){
					ageCount[ageCounter] = ageCount[ageCounter] + 1;
				}//end for 
				
				//step2: reset age of the referenced element
				ageCount[iCounter] = 0;
				
				//step3: make hitFlag page hit
				hitFlag = 1;
				
				//step4: print
				if(programFlag == 0) {
				formatPrint(physicalArray, hitFlag, page, numFrames, numElements);
				}
			}
			
			
			
		}
		
		//case 2: physical page frames is full
		if (arrayFullFlag == 1) {
			
			//add number of references
			numRef++;
			
			//check if the reference page is already in array
			int inFlag = 0;
			int iCounter;
			for (iCounter = 0; iCounter < numFrames; iCounter++){
				//if page in array, raise inFlag
				if (physicalArray[iCounter] == page) {
					inFlag = 1;
					break;
				}
			}//end for
			
			
			//case 2a: reference page is not in the array
			if (inFlag == 0) {
				
				//step1: find victim page, get max age
				int vCounter;
				int maxNumber = -1;
				int maxIndex = -1;
				for(vCounter = 0; vCounter < numFrames; vCounter++) {
					if(ageCount[vCounter] > maxNumber){
						maxNumber = ageCount[vCounter];
						maxIndex = vCounter;
					}
				}//endfor 
				
				//step2: replace victim page with new page
				physicalArray[maxIndex] = page;
				
				//step3: increase age of every element
				int ageCounter;
				for (ageCounter = 0; ageCounter < numFrames; ageCounter++){
					ageCount[ageCounter] = ageCount[ageCounter] + 1;
				}//end for 
				
				//step4: reset age of recently added page to 0
				ageCount[maxIndex] = 0; 
				
				
				//step 5: make hitFlag as page fault
				hitFlag = 0;
				
				//step6: print
				if(programFlag == 0) {
					formatPrint(physicalArray, hitFlag, page, numFrames, numElements);
				}
				//step7: add number of misses
				numMiss++;
				
			}
			
			//case 2b: reference page is already in the array
			if (inFlag == 1){
						
				//step1: increase age of every element
				int ageCounter;
				for (ageCounter = 0; ageCounter < numFrames; ageCounter++){
					ageCount[ageCounter] = ageCount[ageCounter] + 1;
				}//end for 
				
				//step2: reset age of the referenced element
				ageCount[iCounter] = 0;
				
				//step3: make hitFlag page hit
				hitFlag = 1;
				
				//step4: print
				if(programFlag == 0) {
					formatPrint(physicalArray, hitFlag, page, numFrames, numElements);
				}
			}
		
			
			
		}
			
	}
	
	float total = 0;
	
	if (numMiss != 0) {
		total = ((numMiss*1.0)/numRef)*100;
		if(programFlag == 0) {
			printf("Miss rate = %d / %d = %.2f%%\n",numMiss, numRef, total);
		}
		if(programFlag == 1){
			printf("LRU, %2d frames: Miss rate = %d / %d = %0.2f%%\n",numFrames, numMiss, numRef, total);

		}
		
	}
	else {
		if(programFlag == 0) {
			printf("Miss rate = %d /n", 0);
		}
		if(programFlag == 1){
			printf("LRU, %2d frames: Miss rate = %d\n",numFrames, 0);
		}
	}
	
	return total;
}
