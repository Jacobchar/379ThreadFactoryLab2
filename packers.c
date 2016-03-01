#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "factory.h"

// Each packer will extract products one at a time from the
// assembly line. After retrieving 'n' products, the packer 
// tells the user the contents of the package.
