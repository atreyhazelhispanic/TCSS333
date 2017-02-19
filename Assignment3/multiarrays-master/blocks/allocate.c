#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWIDTH 16

//same as array of array function except for the first argument
void printArray(int **a,int nRows,int nCols){
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


 int **a=malloc(nRows * sizeof(void*)); //block of memory to store pointers to rows
 
 for(int i=0;i<nRows;i++)               //blocks for each row to store vlaues
  a[i]=malloc(nCols*sizeof(int));
  
 int **b=malloc(nRows * sizeof(void*));
 for(int i=0;i<nRows;i++)
  b[i]=malloc(nCols*sizeof(int));

 //assign values to array
	int n=0;
	for(int i=0;i<nRows;i++){
	 for(int j=0;j<nCols;j++){
   a[i][j]=n++;
		}
	}	
	
	//for(int i=0;i<nRows;i++)
	// memcpy(b[i],a[i],nCols*sizeof(int)); //This is good  
	//element by element always works

	for(int i=0;i<nRows;i++){
	 for(int j=0;j<nCols;j++){
   b[i][j]=a[i][j];
		}
	}  

	printArray(a,nRows,nCols);
	printArray(b,nRows,nCols);
 for (int i=0;i<nRows;i++)
  if(b[i])free(b[i]);
 if(b)free(b); 
 for (int i=0;i<nRows;i++)
  if(a[i])free(a[i]);
 if(a)free(a); 
 
	return 0;
}
