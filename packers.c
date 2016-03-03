#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "factory.h"

// Each packer will extract products one at a time from the
// assembly line. After retrieving 'n' products, the packer 
// tells the user the contents of the package.

void* startPacker(void* args) {

	Buffer* ASL = args;
	
	Product* box = malloc(ASL->ppb * sizeof(Product));
	
//	while(ASL->numPackaged < (ASL->ppa * ASL->numAssemblers)) {

//		pthread_mutex_lock(&ASL->lock);

//		for (int i = 0; i < ASL->ppb; i++) {
//			if(ASL->numProductsOnLine == 0) { 
//				pthread_cond_wait(&ASL->notEmpty, &ASL->lock);
//			}
//			
//			box[i] = ASL->product[i];
//			ASL->tail = (ASL->tail + 1) % ASL->size;
//			ASL->numProductsOnLine --;
//			ASL->numPackaged ++;	
//		}
		
//		printBox(box, ASL->ppb);
//		pthread_cond_signal(&ASL->notFull);
//		pthread_mutex_unlock(&ASL->lock);
//	}

	// Extract product from line and put in box
	
	// Tell user box is full, start new box
	
	// When the line is empty AND assemblers are all done exit

	free(box);

}

void printBox(Product* box, int ppb) {

	printf("[Packer %ld]: I have a box which contains: ", pthread_self() % 10000);
	for(int i = 0; i < ppb; i ++) {
		printf("%s %d, ", box[i]->colour, box[i]->index);
	}
	printf("%s %d. ", box[ppb]->colour, box[ppb]->index)
	printf("\n");	
}

