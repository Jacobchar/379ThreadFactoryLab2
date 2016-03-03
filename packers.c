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
	
	while(ASL->numPackaged != (ASL->ppa * ASL->numAssemblers)) {
		
		int boxCount = 0;


		for(int i = 0; i < ASL->ppb; i ++) {
			
			pthread_mutex_lock(&ASL->lock);
			
			if(ASL->numPackaged == (ASL->ppa * ASL->numAssemblers)) {
				pthread_mutex_unlock(&ASL->lock);
				break;
			}

			if(ASL->numProductsOnLine == 0) {
				pthread_cond_wait(&ASL->notEmpty, &ASL->lock);
			}
					
			if(ASL->numPackaged == (ASL->ppa * ASL->numAssemblers)) {
				pthread_mutex_unlock(&ASL->lock);
				break;
			}
			
			box[ASL->tail] = ASL->product[ASL->tail];
			ASL->tail = (ASL->tail + 1) % ASL->size;
			ASL->numProductsOnLine --;
			ASL->numPackaged ++;
			boxCount ++;
			pthread_cond_broadcast(&ASL->notFull);
			pthread_mutex_unlock(&ASL->lock);
		}
	
		pthread_mutex_lock(&ASL->print);
		printBox(box, boxCount);	
		pthread_mutex_unlock(&ASL->print);
	}

	free(box);
	pthread_exit(NULL);
}

void printBox(Product* box, int ppb) {

	printf("[Packer %ld]: I have a box which contains: ", pthread_self() % 10000);
	for(int i = 0; i < ppb; i ++) {
		printf("%s %d ", box[i].colour, box[i]. index);
	}
	printf("\n");
}

