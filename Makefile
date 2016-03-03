DEPS = factory.h

Factory: factory.c packers.c assemblers.c
	gcc -std=c99 -pthread -o Factory factory.c packers.c assemblers.c -I.

clean:
	rm Factory
