DEPS = factory.h

Factory: factory.c
	gcc -std=c99 -D _XOPEN_SOURCE=600 -o Factory factory.c -I.
