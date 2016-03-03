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

int main(int numArgs, char* input[]) {
	
	if(numArgs != VALID_INPUT){
		printf("Invalid number of arguments \n");
		return ERROR;
	}
	
	int numAssemblers = atoi(input[1]);
	int numPackers = atoi(input[2]);
	int sizeAssemblyLine = atoi(input[3]);
	int numProductsPerBox = atoi(input[4]);
	int numProductsPerAssembler = atoi(input[5]);
		
	// Setup AssemblyLine
	Buffer* ASL = malloc(sizeof(Buffer));
	Product* products = malloc(sizeAssemblyLine * sizeof(Product));
	ASL->size = sizeAssemblyLine;
	ASL->ppb = numProductsPerBox;
	ASL->ppa = numProductsPerAssembler;
	ASL->head = 0;
	ASL->tail = 0;
	ASL->numAssemblers = numAssemblers;
	ASL->numPackaged = 0;
	ASL->numProductsOnLine = 0;
	ASL->product = products;
	
	pthread_t* assemblerThreads = malloc(numAssemblers * sizeof(pthread_t));
	pthread_t* packerThreads = malloc(numPackers * sizeof(pthread_t));
	
	// Spawn assemblers
	for (int i = 0; i < numAssemblers; i ++) {
		if(pthread_create(&assemblerThreads[i] , NULL, startAssembler, ASL)) {
			perror("Error Creating Thread");
		}
	}
	
	// Spawn packers
	for (int i = 0; i < numPackers; i ++) {;
		if(pthread_create(&packerThreads[i] , NULL, startPacker, ASL)) {
			perror("Error Creating Thread");
		}
	}
	
	for (int i = 0; i < numAssemblers; i ++) {
		pthread_join(assemblerThreads[i], NULL);
	}
	
	for (int i = 0; i < numPackers; i ++) {
		pthread_join(packerThreads[i], NULL);
	}

	free(assemblerThreads);
	free(packerThreads);
	free(ASL);
	free(products);
	return 0;
}

