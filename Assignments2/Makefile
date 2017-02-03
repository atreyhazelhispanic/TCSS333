CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm

testArraysStrings: arraysStrings.o testArraysStrings.o
	gcc arraysStrings.o testArraysStrings.o -o testArraysStrings

arraysStrings.o: arraysStrings.c
	gcc -c arraysStrings.c

testArraysStrings.o: testArraysStrings.c arraysStrings.h
	gcc -c testArraysStrings.c

clean:
	rm *.o
	rm testArraysStrings