CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm
OBJECTS = testArraysStrings.o arraysStrings.o

all: testArraysStrings

testArraysStrings: testArraysStrings.o arraysStrings.o
	$(CC) $(CFLAGS) -o testArraysStrings testArraysStrings.o arraysStrings.o

testArraysStrings.o: testArraysStrings.c arraysStrings.h
	$(CC) $(CFLAGS) -c testArraysStrings.c

arraysStrings.o: arraysStrings.c arraysStrings.h
	$(CC) $(CFLAGS) -c arraysStrings.c

clean:
	rm *.o
	rm testArraysStrings