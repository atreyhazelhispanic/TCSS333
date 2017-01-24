all: runIt

runIt: vectors.o testVectors.o
	gcc vectors.o testVectors.o -o runIt

vectors.o: vectors.c
	gcc -c vectors.c

testVectors.o: testVectors.c
	gcc -c testVectors.c

clean:
	rm *.o
	rm testVectors