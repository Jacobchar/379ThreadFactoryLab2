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

	// Extract product from line and put in box
	
	// Tell user box is full, start new box
	
	// When the line is empty AND assemblers are all done exit


}

https://www.cs.mtu.edu/~shene/NSF-3/e-Book/SEMA/TM-example-buffer.html
