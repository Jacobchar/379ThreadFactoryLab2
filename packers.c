#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "factory.h"

// Each packer will extract products one at a time from the
// assembly line. After retrieving 'n' products, the packer 
// tells the user the contents of the package.

/*
 * @brief Function called when a packer thread is created
 * @param args - a generic which in our case is the AssemblyLine structure
 * @return void*
 */
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
			
			box[i] = ASL->product[ASL->tail];
			printf("\n%d\n", ASL->tail);
			ASL->tail = (ASL->tail + 1) % ASL->size;
			printf("\n%d\n", ASL->tail);
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

/*
 * @brief Function called to print the contents of the packaged box done by the packer
 * @param box A Product array representing the packaged box
 * @param ppb Products Per Box an int that tells the function how many elements to print
 * @return void
 */

void printBox(Product* box, int ppb) {

	printf("[Packer %ld]: I have a box which contains: ", pthread_self() % 10000);
	for(int i = 0; i < ppb; i ++) {
		printf("%s %d ", box[i].colour, box[i]. index);
	}
	printf("\n");
}

