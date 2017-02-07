CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm

all: testArraysStrings vectors

testArraysStrings: testArraysStrings.o arraysStrings.o 
	$(CC) $(CFLAGS) testArraysStrings.o arraysStrings.o vectors.o -o testArraysStrings

testArraysStrings.o: testArraysStrings.c arraysStrings.h
	$(CC) $(CFLAGS) -c testArraysStrings.c

arraysStrings.o: arraysStrings.c arraysStrings.h
	$(CC) $(CFLAGS) -c arraysStrings.c

vectors: testVectors.o vectors.o
	$(CC) $(CFLAGS) testVectors.o vectors.o -o vectors

testVectors.o: testVectors.c vectors.h
	$(CC) $(CFLAGS) testVectors.c

vectors.o: vectors.c vectors.h
	$(CC) $(CFLAGS) -c vectors.c

clean:
	rm *.o
	rm testArraysStrings
	rm vectors