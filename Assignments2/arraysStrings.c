#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include "arraysStrings.h"

//Part 1 - 2 points
//write a function joinrev that takes 2 strings and returns a 3rd string that is th first string followed by the 2nd string reversed
//Output should be:
//Hello dlroW
//Hint: joining the strings first and then reversing part of the joined string may be easier - ymmv
char* joinrev(char alpha[], char *beta){
	//char arrays decay into pointers.
	if(NULL == alpha || NULL == beta)
		return NULL;

	char *temp = malloc(strlen(alpha) + strlen(beta) + 1);
	char beta2[strlen(beta) + 1];
	strcpy(beta2, beta);
	int length = strlen(beta);
	int left = 0;
	int right = length - 1;

	while(left < right){
		char temporary = beta2[left];
		beta2[left] = beta2[right];
		beta2[right] = temporary;
		left++;
		right--;
	}

	strcpy(temp, alpha);
	strcat(temp, beta2);

	return temp;
}

//Part 2 - 2 points 
//write a function joinrev_generic that takes pointers to any two arrays, a typesize, and the number of elements in each array and does the same 
//thing as joinrev except that it will return a void pointer and will work on any type of array. HINT - copy the code from part 1 and change the code so that the pointer arithmetic is done explicitly and the copies are done using memcpy and memmove as in the class example reverse3
void* joinrev_generic(void* alpha, void* beta, size_t size, size_t nmembA, size_t nmembB){
	if(alpha == NULL || beta == NULL)
		return NULL;

	void* result = malloc((nmembA + nmembB) * size);
	void* beta2 = malloc(nmembB * size);
	memcpy(beta2, beta, nmembB * size);
	char* traverse = (char*) beta2;
	int left = 0;
	int right = nmembB - 1;

	while(left < right){
		char temporary = traverse[left];
		traverse[left] = traverse[right];
		traverse[right] = temporary;
		left++;
		right--;
	}

	void* alpha2 = malloc((nmembA + nmembB) * size);
	memcpy(alpha2, alpha, nmembA * size);
	memcpy(alpha2 + (nmembA * size), beta2, nmembB * size);
	memmove(result, alpha2, (nmembA + nmembB) * size);
	free(beta2);
	free(alpha2);

	return result;
}

//Part 3 - 2 points
//Write a function readTextAddBinary that takes two strings (filenames) and returns 0 if the function completes successfully. The function reads from the first filename, a set of vectors, 2 per line and add them together and writes out a binary file (the second filename) with the new vectors (just the vectors - no spaces or other delimiters)
//A test file is given to you along with the expected output - you can use the Unix diff function to compare your output with the expected output in testFiles
int readTextAddBinary(char* fileIn, char* fileOut){
	FILE *theRead = fopen(fileIn, "r");
	FILE *theWrite = fopen(fileOut, "w+");
	float first, second, third, fourth, fifth, sixth;
	fscanf(theRead, "%f %f %f %f %f %f", &first, &second, &third, &fourth, &fifth, &sixth);
	char c = fgetc(theRead);
	
    while (c != EOF)
    {
        c = fgetc(theRead);
        if(c == '\n');{
        	vector_print(vector_add(vector_init(first, second, third), vector_init(fourth, fifth, sixth)));
        	fscanf(theRead, "%f %f %f %f %f %f", &first, &second, &third, &fourth, &fifth, &sixth);
        }
        
    }
    fclose(theRead);
    
	return 0;
}