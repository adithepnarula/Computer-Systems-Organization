#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void formatPrint(int array[], int hitFlag, int page, int frameSize, int numElements){
	
	//print page
	if (page < 10) {
		printf(" %d:  ", page);
		
	}
	else{
		printf("%d:  ", page);
	}
	printf("[");
	int i;
	for (i = 0; i < frameSize - 1; i++) {
		
		//only if there are pages in the array slot
		if ( i < numElements) {
			int number = array[i];
			//two digits
			if (number - 9 > 0) {
				printf("%d%s",number,"|");
			}
			else {
				printf(" %d%s",number, "|");
			}
		}
		
		//the rest of the pages are empty
		else {
			
			printf("  %s", "|"); 
			
		}
	}//end for
	
	//print last element
	
	if ( i < numElements ) {
		int number = array[i];
			//two digits
			if (number - 9 > 0) {
				printf("%d%s",number,"]");
			}
			else {
				printf(" %d%s", number, "]");
			}
	}
	else {
			printf("  %s", "]"); 
	}
	//page fault
	if (hitFlag == 0) {
		printf("  %s", "F");
		printf("\n");
	}
	else {
		printf("\n");	
	}
}

