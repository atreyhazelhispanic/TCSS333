#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXWIDTH 128


typedef struct{
	int height;
	int width;
	char (*pixArray)[MAXWIDTH];
}pict;

pict *pict_init(char *filename,int height,int width){
	pict *p=malloc(sizeof(pict));
	p->height=height;
	p->width=width;
	p->pixArray=malloc(height*sizeof(char[MAXWIDTH]));
	FILE *fp=fopen(filename,"r");
	for(int i=0;i<height;i++){
		fgets(p->pixArray[i],MAXWIDTH,fp);
	}	
	fclose(fp);
	return p;
}

void pict_print(pict *p){
	for (int i=0;i<p->height;i++){
		for (int j=0;j<p->width;j++){
		 printf("%c",p->pixArray[i][j]);	
		}
		printf("\n");
	}		
}	

	
void pict_destroy(pict **p){
	pict *this_ptr=*p;
	if(this_ptr->pixArray) free(this_ptr->pixArray);
	if(*p) free(*p);
}	
int main(){
	pict *p=pict_init("santa.txt",16,61);
	pict_print(p);
	pict_destroy(&p);
	return 0;
}
