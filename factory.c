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
	// assemblyline = (AssemblyLine *)malloc(sizeof(AssemblyLine));
	// variables of structure here
	
	
	pthread_t assemblerThreads[numAssemblers];
	pthread_t packerThreads[numPackers];
	
	// Spawn assemblers
	for (int i = 0; i < numAssemblers; i ++) {
		int* assemblyArgs[] = {sizeAssemblyLine, numProductsPerAssembler, i};
		printf("Creating Assembler Thread: %d", i);
		if(!pthread_create(&assemblerThreads[i] , NULL, startAssembler, assemblyArgs)); {
			perror("Error Creating Thread"):
		}
	}
	
	// Spawn packers
	for (i = 0; i < numPackers; i ++) {
		int* packerArgs[] = {sizeAssemblyLine, numProductsPerBox, i};
		printf("Creating Packer Thread: %d", i);
		if(!pthread_create(&assemblerThreads[i] , NULL, startPacker, packerArgs)); {
			perror("Error Creating Thread");
		}
	}
	
	for (i = 0; i < numAssemblers; i ++) {
		pthread_join(assemblerThreads[i], NULL);
		printf("Assembler %d has completed.", i);
	}
	
	for (i = 0; i < numPackers; i ++) {
		pthread_join(packerThreads[i], NULL);
		printf("Packer %d has completed", i);
	}
	
	//free(assemblyline);
	printf("The factory has closed for the day.");
	return 0;
}
