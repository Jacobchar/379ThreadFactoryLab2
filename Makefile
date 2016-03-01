DEPS = factory.h

Factory: factory.c 
	gcc -std=c99 -Wall -pthread -o Factory factory.c packers.c assemblers.c -I.

clean:
	rm Factory
