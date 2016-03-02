#define VALID_INPUT 6
#define ERROR -1

#define AssemblerThreads 1
#define PackerThreads 2
#define AssemblyLine 3
#define ProductsPerBox 4
#define ProductsPerAssembler 5

void* startAssembler(void* args);
void* startPacker(void* args);

typedef struct {
	char* colour;
	int index;
} Product;

typedef struct  {
	char* colour;
	int numProduce;
} Assembler;

typedef struct {
	int perBox;
	int numBoxes;
} Packer;

typedef struct  {
	
} AssemblyLine;
