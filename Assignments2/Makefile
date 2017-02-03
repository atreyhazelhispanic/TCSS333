CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm
OBJECTS = testArraysStrings.o arraysStrings.o

arrays.exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o arrays.exe

testArraysStrings.o: testArraysStrings.c
	$(CC) $(CFLAGS) -c testArraysStrings.c

arraysStrings.o: arraysStrings.c
	$(CC) $(CFLAGS) -c arraysStrings.c

clean:
	rm *.o
	rm testArraysStrings