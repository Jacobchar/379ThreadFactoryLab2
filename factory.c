#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "factory.h"

// This is our main function which is responisble for the overall
// control of the factory. It creates our assembly line (bounded 
// buffer array), spawns a assembler and b packer threads. It waits 
// until all producets have been packaged before closing the threads.

int main(int numArgs, char* input[]){
	
	if(numArgs != VALID_INPUT){
		printf("Invalid number of arguments \n");
		return ERROR;
	}
	
	int numAssembler = atoi(input[1]);
	int numPackers = atoi(input[2]);
	int sizeAssemblyLine = atoi(input[3]);
	int numProductsPerBox = atoi(input[4]);
	int numProductsPerAssembler = atoi(input[5]);

}
