#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWIDTH 16

//same as for pointer to blocks
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
 
 int **a=malloc(nRows * sizeof(void*));
 a[0]=malloc(nRows*nCols*sizeof(int));
 for(int i=1;i<nRows;i++)
  a[i]=a[i-1]+nCols;
 
 int **b =malloc(nRows * sizeof(void*));
 b[0]=malloc(nRows*nCols*sizeof(int));
 for(int i=1;i<nRows;i++)
  b[i]=b[i-1]+nCols;
   
	int n=0;
	for(int i=0;i<nRows;i++)
	  for(int j=0;j<nCols;j++)
    a[i][j]=n++;
	
	//memcpy(b,a,nRows*nCols*sizeof(int)); //CAN use this because it is a single block
	
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
	
	
 if(a[0]) free(a[0]); //free the values block
 if(a) free(a);       //free the pointers block 
 if(b[0]) free(b[0]);
 if(b) free(b);
  
	return 0;
}
