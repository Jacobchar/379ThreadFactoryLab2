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
	
	pthread_t assemblerThreads[numAssemblers];
	pthread_t packerThreads[numPackers];
	
	// Spawn assemblers
	for (int i = 0; i < numAssemblers; i ++) {
		printf("Creating Assembler Thread: %d\n", i);
		int err = 0;
		pthread_create(&assemblerThreads[i] , NULL, startAssembler, ASL);
		if(err != 0) {
			perror("Error Creating Thread");
		}
	}
	
	// Spawn packers
	for (int i = 0; i < numPackers; i ++) {
		printf("Creating Packer Thread: %d\n", i);
		int err = pthread_create(&assemblerThreads[i] , NULL, startPacker, ASL);
		if(err != 0) {
			perror("Error Creating Thread");
		}
	}
	
	for (int i = 0; i < numAssemblers; i ++) {
		pthread_join(assemblerThreads[i], NULL);
		printf("Assembler %d has completed.\n", i);
	}
	
	for (int i = 0; i < numPackers; i ++) {
		pthread_join(packerThreads[i], NULL);
		printf("Packer %d has completed\n", i);
	}

	free(ASL);
	free(products);
	return 0;
}

