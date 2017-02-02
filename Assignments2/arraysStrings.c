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
	void* beta2;
	memcpy(beta2, beta, nmembB);
	char* traverse = beta2;
	int left = 0;
	int right = strlen(beta2) - 1;
	printf("%d", right);



	return result;
}