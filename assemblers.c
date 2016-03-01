#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "factory.h"

// Each assembler creats a product of a unique colout with each
// product being numbered sequentially. After creating a product, 
// the assembler places it on the assembly line. If the line is 
// full then theymust wait until a slot becomes available.
