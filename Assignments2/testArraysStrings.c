#include <stdio.h>
#include <stdlib.h>
// #include "vectors.c"
// #include "arraysStrings.c"
#include "arraysStrings.h"

int main(){
	char a[]="Hello";
	char *b=" World ";
	char *c=joinrev(a,b);
	printf("%s\n",c);
	
	vector vas[3]={vector_init(1,1,1),vector_init(2,2,2),vector_init(3,3,3)};
	vector vbs[3]={vector_init(4,4,4),vector_init(5,5,5),vector_init(6,6,6)};
	vector *vcs=(vector *)joinrev_generic((void*)vas,(void*)vbs,sizeof(vector),sizeof(vas)/sizeof(vector),sizeof(vbs)/sizeof(vector));
	for(int i=0;i<(sizeof(vas)+sizeof(vbs))/sizeof(vector);i++){
 	vector_print(vcs[i]);
	}
	
	if(readTextAddBinary("vectors.txt","vectors.bin")){
		fprintf(stderr,"A fatal error occurred for readTextAddBinary\n");
		return 1;  
	}
	
	if(readBinaryNormText("vectors.bin","norm.txt")){
		fprintf(stderr,"A fatal error occurred for readBinaryNormText\n");
		return 1; 
	}	
	
	/*
	//Part 5 - 2 points
	//Write a function readNormTextWriteNormBinary that takes two strings as input (filenames) and returns 0 if the function completes successfully.. The first argument is the text file of type produced in part 4.  Read in the line using fgets or fread. Either use realloc or check for the size of the file using fseek, ftell to allocate enough space to store the line. Then use strtok to parse the file. Print the results out to a binary file in the same format as the binary file produced in part 3. Remember to free the memory.
	
	if(readNormTextWriteNormBinary("norm.txt","norm.bin")){
		fprintf(stderr,"A fatal error occurred for readNormTextWriteNormBinary\n");
		return 1; 
	}	
	
	//Bonus - 1 bonus point
	//Write a function wc that reads in the text file given and count the number of lines, number of words and number of characters. The output should be the same as given by the UNIX function wc i.e by typing the command "wc gettysburg.txt"
	//Hint read in char by char and use the built in C isspace() function to determine if the character is whitespace
	
	if(wc("gettysburg.txt")){
		fprintf(stderr,"A fatal error occurred for gettysburg.txt\n");
		return 1;	
	}*/
	if(c) free(c);
	if(vcs) free	(vcs); 
	return 0;
}