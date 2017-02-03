CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm

testArraysStrings: testArraysStrings.o arraysStrings.o vectors.o
	$(CC) $(CFLAGS) testArraysStrings.o arraysStrings.o vectors.o -o testArraysStrings

testArraysStrings.o: testArraysStrings.c arraysStrings.h
	$(CC) $(CFLAGS) -c testArraysStrings.c

arraysStrings.o: arraysStrings.c
	$(CC) $(CFLAGS) -c arraysStrings.c

vectors.o: vectors.c
	$(CC) $(CFLAGS) -c vectors.c

clean:
	rm *.o
	rm testArraysStrings