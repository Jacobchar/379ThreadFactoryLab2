#define VALID_INPUT 6
#define ERROR -1

#define AssemblerThreads 1
#define PackerThreads 2
#define AssemblyLine 3
#define ProductsPerBox 4
#define ProductsPerAssembler 5

typedef struct Product {
	char* colour;
	int index;
};

typedef struct Assembler {
	char* colour;
	int numProduce;
};

typedef struct Packer {
	int perBox;
	int numBoxes;
};

typedef struct AssemblyLine {
	
};
