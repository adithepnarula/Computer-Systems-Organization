#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void printarray(int *a, int size);
 
int main(int argc, char *argv[]){
	
	//first argument is the file name you are running, so we need +1 arguments
	//argc - number of arguments
	//argv - array containing arguments 

	
	if (argc != 5) {
		printf("Invalid number of parameters %s\n", argv[0]);
		exit(1);
	}
	
	
	
	//read min number of frames
	int minNumFrames;
	sscanf(argv[1], "%d", &minNumFrames);
	if (minNumFrames < 1 || minNumFrames > 100) {
		printf("Invalid number of min frames\n");
		exit(1);
	}
	
	//read max number of frames
	int maxNumFrames;
	sscanf(argv[2], "%d", &maxNumFrames);
	if (maxNumFrames < 1 || maxNumFrames > 100 || maxNumFrames <= minNumFrames) {
		printf("Invalid number of max frames %d\n", maxNumFrames);
		exit(1);
	}
	
		
	//read increment number of frames
	int incrementNumFrames;
	sscanf(argv[3], "%d", &incrementNumFrames);
	if (incrementNumFrames < 0 || incrementNumFrames%1 != 0) {
		printf("Invalid number of increment frames\n");
		exit(1);
	}
	
	
	FILE *file = fopen(argv[4], "r");
	//exit if file doesn't work
	if (file == 0){
		printf("Invalid file %s\n", argv[4]);
	}
	
	
	int numberOfElements = 1000;
	int* inputArray = (int *)malloc(numberOfElements*sizeof(int));
	

	
	int page;
	int x;
	
	int size = 0;
	
	//count number of pages to find out array size
	do { 
		x = fscanf(file, "%d", &page);
		//check if input is valid
		if(x > 0) {
			if (size == numberOfElements-1) {
				
				numberOfElements = numberOfElements * 2;
				inputArray = (int*)realloc(inputArray,numberOfElements*sizeof(int));
			
			}
		inputArray[size] = page;
		size++;
		}
	}while(x > 0);
	
	fclose(file);
	
	FILE *outfile = fopen("outfile.txt","w");
	if (outfile == NULL){
		printf("Cannot open file\n");
		exit(1);
	}
	
	

	int programFlag = 1;
	
		
	
	fprintf(outfile,"Number of frames: ");
	
	
	int i = minNumFrames;
	
	//write number of frames
	for (;i <= maxNumFrames; i = i + incrementNumFrames) {
		fprintf(outfile, "%d ", i);
	}//end for
		
	fprintf(outfile,"\n");
	fprintf(outfile,"LRU: ");
	
	i = minNumFrames;

	//LRU
	for (;i <= maxNumFrames; i = i + incrementNumFrames) {
		float result = LRU(i, inputArray, size, programFlag);
		fprintf(outfile, " %.2f ", result);
	}//end for 
	
	fprintf(outfile,"\n");
	fprintf(outfile,"FIFO: ");
	
	
	i = minNumFrames;
	printf("\n");
	//FIFO
	for (;i <= maxNumFrames; i = i + incrementNumFrames) {
		float result = fifo(i, inputArray, size, programFlag);
		fprintf(outfile, " %.2f ", result);
	}//end for
	printf("\n");
	i = minNumFrames;
	
	fprintf(outfile,"\n");
	fprintf(outfile,"Narula: ");
	
	//Narula
	for (;i <= maxNumFrames; i = i + incrementNumFrames) {
		float result = narula_priazza_mango_vokda(i, inputArray, size, programFlag);
		fprintf(outfile, " %.2f ", result);
	}//end for
	
	fclose(outfile);
	printf("\n");
	return 1;
}



void printarray(int *a, int size) {
		
	int i;
	for (i = 0; i < size; i ++) {
		printf("%d ", *(a+i));
	}
	printf("\n");
	
}


