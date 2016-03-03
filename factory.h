#define VALID_INPUT 6
#define ERROR -1

#define MAXCOLOURS 147
#define AssemblerThreads 1
#define PackerThreads 2
#define AssemblyLine 3
#define ProductsPerBox 4
#define ProductsPerAssembler 5

typedef struct Product {
	const char* colour;
	int index;
} Product;

typedef struct Buffer {
	int size;
	int ppb, ppa;
	int head, tail;
	int numProductsOnLine;
	int numPackaged;
	int numAssemblers;
	Product* product;
	pthread_mutex_t lock;
	pthread_mutex_t print;
	pthread_cond_t notEmpty;
	pthread_cond_t notFull;
} Buffer;

void* startAssembler(void* args);
void* startPacker(void* args);
Product* getProduct();
void printBox(Product* box, int ppb);
