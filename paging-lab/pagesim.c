#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[]){
	
	//first argument is the file name you are running, so we need +1 arguments
	//argc - number of arguments
	//argv - array containing arguments 
	int algoFlag = -1;
	
	if (argc != 4) {
		printf("Invalid number of parameters, 3 required total.  %s\n", argv[0]);
		exit(1);
	}
	
	
	//read number of frames
	int numFrames;
	sscanf(argv[1], "%d", &numFrames);
	if (numFrames < 1 || numFrames > 100) {
		printf("Invalid number of frames. Must be 1 to 100.");
		exit(1);
	}
	
	
	//make sure algorithm is valid
	char* algorithm = argv[3];
	if ((strcmp(algorithm,"fifo") == 0)){
		algoFlag = 1;
	}
	else if ((strcmp(algorithm,"lru") == 0)){
		algoFlag = 2;
	}
	else if((strcmp(algorithm,"extra")==0)){
		algoFlag = 3;
	}
	else{
		printf("Please enter only lower case. Example enter fifo not FIFO. For extra credit enter \'extra\' Invalid algorithm.\n");
		exit(1);
	}

	FILE *file = fopen(argv[2], "r");
	//exit if file doesn't work
	if (file == 0){
		printf("Invalid file %s\n", argv[2]);
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
			if (size == numberOfElements) {
				
				numberOfElements = numberOfElements * 2;
				inputArray = (int*)realloc(inputArray,numberOfElements*sizeof(int));
			
			}
		inputArray[size] = page;
		size++;
		}
	}while(x > 0);
	
	fclose(file);
	
	//for print statement
	int programFlag = 0;
	
	if (algoFlag == 1){
		fifo(numFrames, inputArray, size, programFlag);
	}
	else if (algoFlag == 2) {
		LRU(numFrames, inputArray, size, programFlag);
	}
	else if (algoFlag == 3){
		narula_priazza_mango_vokda(numFrames, inputArray, size, programFlag);
	}
	
	return 1;
}
