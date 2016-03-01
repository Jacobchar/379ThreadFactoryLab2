#define VALID_INPUT 6
#define ERROR -1

#define AssemblerThreads 1
#define PackerThreads 2
#define AssemblyLine 3
#define ProductsPerBox 4
#define ProductsPerAssembler 5

typedef struct {
	char* colour;
	int index;
} Product;

typedef struct {
	char* colour;
	int numProduce;
} Assembler;

typedef struct {
	int perBox;
	int numBoxes;
} Packer;

typedef struct {
	void *buffer
	void *buffer_end
	size_t capacity;
	size_t count;
	size_t size;
	void *head;
	void *tail; 
} AssemblyLine;
