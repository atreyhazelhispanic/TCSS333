#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWIDTH 16

void printArray(int a[][MAXWIDTH],int nRows,int nCols){
	for(int i=0;i<nRows;i++){
		for(int j=0;j<nCols;j++){
			printf("a[%d][%d]=%d ",i,j,a[i][j]);
		}
		printf("\n"); 
	}
}	

int main(){
	int nRows=3;
	int nCols=2;
	int a[3][MAXWIDTH]={{0,1},{2,3},{4,5}};
	printArray(a,nRows,nCols);
	int (*b)[MAXWIDTH]=malloc(nRows*sizeof(int[MAXWIDTH]));
	
	//memcpy(b,a,nRows*sizeof(int[MAXWIDTH]); //copy entire block works fine in this case
	//for(int i=0;i<nRows;i++){
	// memcpy(b[i],a[i],nCols*sizeof(int));   //copy each row works too - and is more general
 //}
 
 //can ALWAYS do element by element - usually not any slower
 //for(int i=0;i<nRows;i++){
	// for(int j=0;j<nCols;j++){
 //  b[i][j]=a[i][j];
 // }
 //}
 
	//int n; example of error due to uninitialized variable
	int n=0; //correct code
	for(int i=0;i<nRows;i++)
	 for(int j=0;j<nCols;j++)
   b[i][j]=n++;
	printArray(b,nRows,nCols);
	if(b)free(b); //only need to free b <- leave out and will give an error in valgrind
	//free(b); <-- uncomment to get a double free error in valgrind
	return 0;
}
