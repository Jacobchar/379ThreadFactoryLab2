#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "factory.h"

const char *COLOURS[] = {"AliceBlue","AntiqueWhite","Aqua","Aquamarine","Azure",
"Beige","Bisque","Black","BlanchedAlmond","Blue","BlueViolet","Brown","BurlyWood",
"CadetBlue","Chartreuse","Chocolate","Coral","CornflowerBlue","Cornsilk","Crimson",
"Cyan","DarkBlue","DarkCyan","DarkGodenRod","DarkGray","DarkGrey","DarkGreen",
"DarkKhaki","DarkMagenta","DarkOliveGreen","Darkorange","DarkOrchid","DarkRed",
"DarkSalmon","DarkSeaGreen","DarkSlateBlue","DarkSlateGray","DarkSlateGrey",
"DarkTurquoise","DarkViolet","DeepPink","DeepSkyBlue","DimGray","DimGrey",
"DodgerBlue","FireBrick","FloralWhite","ForestGreen","Fuchsia","Gainsboro",
"GhostWhite","God","GodenRod","Gray","Grey","Green","GreenYellow","HoneyDew",
"HotPink","IndianRed","Indigo","Ivory","Khaki","Lavender","LavenderBlush",
"LawnGreen","LemonChiffon","LightBlue","LightCoral","LightCyan",
"LightGodenRodYellow","LightGray","LightGrey","LightGreen","LightPink",
"LightSalmon","LightSeaGreen","LightSkyBlue","LightSlateGray","LightSlateGrey",
"LightSteelBlue","LightYellow","Lime","LimeGreen","Linen","Magenta","Maroon",
"MediumAquaMarine","MediumBlue","MediumOrchid","MediumPurple","MediumSeaGreen",
"MediumSlateBlue","MediumSpringGreen","MediumTurquoise","MediumVioletRed",
"MidnightBlue","MintCream","MistyRose","Moccasin","NavajoWhite","Navy","OdLace",
"Olive","OliveDrab","Orange","OrangeRed","Orchid","PaleGoldenRod","PaleGreen",
"PaleTurquoise","PaleVioletRed","PapayaWhip","PeachPuff","Peru","Pink","Plum",
"PowderBlue","Purple","Red","RosyBrown","RoyalBlue","SaddleBrown","Salmon",
"SandyBrown","SeaGreen","SeaShell","Sienna","Silver","SkyBlue","SlateBlue",
"SlateGray","SlateGrey","Snow","SpringGreen","SteelBlue","Tan","Teal","Thistle",
"Tomato","Turquoise","Violet","Wheat","White","WhiteSmoke","Yellow","YellowGreen"};

// Each assembler creates a product of a unique colout with each
// product being numbered sequentially. After creating a product, 
// the assembler places it on the assembly line. If the line is 
// full then they must wait until a slot becomes available.

/*
 * @brief Function called when an assembler thread is created
 * @param args - a generic which in our case is the AssemblyLine structure
 * @return void*
 */
void* startAssembler(void* args) {

	Buffer* ASL = args;
	Product* p = getProduct();
	
	for(int i = 0; i < ASL->ppa; i ++) {
	
		pthread_mutex_lock(&ASL->lock);
		
		if(ASL->numProductsOnLine == ASL->size) {
			pthread_cond_wait(&ASL->notFull, &ASL->lock);
		}
		
		p->index = i;
		ASL->product[ASL->head] = *p;
		ASL->head = (ASL->head + 1) % ASL->size;
		ASL->numProductsOnLine ++;
		
		pthread_cond_signal(&ASL->notEmpty);
		pthread_mutex_unlock(&ASL->lock);	

	}
	
	free(p);
	pthread_exit(NULL);	
}

/*
 * @brief Creates the coloured product unique to each assembler thread
 * @return Product*
 */
Product* getProduct() {
	Product* product = malloc(sizeof(Product));
	long index = pthread_self() % MAXCOLOURS;
	product->colour = COLOURS[index];
	product->index = 0;
	return product;
}	
