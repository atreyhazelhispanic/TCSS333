testVectors: vectors.o testVectors.o
	gcc vectors.o testVectors.o -o testVectors

vectors.o: vectors.c
	gcc -c vectors.c

testVectors.o: testVectors.c vectors.h
	gcc -c testVectors.c

clean:
	rm *.o
	rm testVectors