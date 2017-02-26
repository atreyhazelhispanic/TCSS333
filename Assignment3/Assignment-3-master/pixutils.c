#include "pixutils.h"

//private methods -> make static
static pixMap* pixMap_init(unsigned char arrayType);
static pixMap* pixMap_copy(pixMap *p);

static pixMap* pixMap_init(unsigned char arrayType){
	pixMap* pointer = calloc(1, sizeof(pixMap));
	pointer -> arrayType = arrayType;

	return pointer;
}	

void pixMap_destroy (pixMap **p){
	if(!p)
 		fprintf(stderr, "None exist \n");

	int rows = (**p).imageHeight;

	free((**p).image);

 	switch((**p).arrayType){
 		case '0':
 			for(int i=0; i<rows; i++){
 				free(*(*p)->pixArray_arrays[i]);
 			}
 			free(p);
 			break;
 		case '1':
 			for(int i=0; i<rows; i++){
 				free((**p).pixArray_blocks[i]);
 			}
 			free(p);
 			break;
 		case '2':
 			for(int i=0; i<rows; i++){
 				free((**p).pixArray_overlay[i]);
 			}
 			free(p);
 			break;
 	}
}

pixMap *pixMap_read(char *filename,unsigned char arrayType){
 	//library call reads in the image into p->image and sets the width and height
	pixMap *p=pixMap_init(arrayType);
 	int error;
 	if((error=lodepng_decode32_file(&(p->image), &(p->imageWidth), &(p->imageHeight),filename))){
  		fprintf(stderr,"error %u: %s\n", error, lodepng_error_text(error));
  		return 0;
	}

	int columns = p -> imageWidth;
	int rows = p -> imageHeight;
 	//allocate the 2-D rgba arrays
	p->pixArray_blocks = malloc(rows*sizeof(rgba));
	p->pixArray_overlay = malloc(rows*sizeof(rgba));

	if (arrayType == 0){
  		//can only allocate for the number of rows - each row will be an array of MAXWIDTH
  		//copy each row of the image into each row
		p -> pixArray_arrays = malloc(rows*sizeof(rgba[MAXWIDTH]));
		for(int i=0; i<rows; i++)
			memcpy(&p->pixArray_arrays[i], &p->image[i], columns*sizeof(rgba));
	}	
	else if (arrayType == 1){
		//allocate a block of memory (dynamic array of p->imageHeight) to store the pointers
		//use a loop allocate a block of memory for each row
		//copy each row of the image into the newly allocated block
		p -> pixArray_blocks = malloc(rows*MAXWIDTH*sizeof(rgba));
		for(int i=0; i<rows; i++)
			memcpy(&p->pixArray_blocks[i], &p->image[i], columns*sizeof(rgba));
 	}
	else if (arrayType == 2){
  		//allocate a block of memory (dynamic array of p->imageHeight) to store the pointers
  		//set the first pointer to the start of p->image
  		//each subsequent pointer is the previous pointer + p->imageWidth
  		p -> pixArray_overlay = malloc(rows*sizeof(rgba));
  		for(int i=0; i<rows; i++)
  			p->pixArray_overlay[i] = (rgba*) &p->image[i];
	}
	else{
		return 0;
	}				
	return p;
}

int pixMap_write(pixMap *p,char *filename){
	int error=0;
	int columns = p->imageWidth;
	int rows = p->imageHeight;

	//for arrayType 1 and arrayType 2 have to write out a controws to the image using memcpy
	if(p->arrayType == 0){
   		//have to copy each row of the array into the corresponding row of the image	
		p -> image = malloc(rows*sizeof(rgba[MAXWIDTH]));
		for(int i=0; i<rows; i++)
			memcpy(&p->image[i], &p->pixArray_arrays[i], columns*sizeof(rgba));
	}	
	else if(p->arrayType == 1){
   		//have to copy each row of the array into the corresponding row of the image
		p -> image = malloc(rows*MAXWIDTH*sizeof(rgba));
		for(int i=0; i<rows; i++)
			memcpy(&p->image[i], &p->pixArray_blocks[i], columns*sizeof(rgba));
	}
	else if(p->arrayType == 2){
		p -> image = malloc(rows*columns*sizeof(rgba));
		for(int i=0; i<rows; i++)
			memcpy(&p->image[i], &p->pixArray_overlay, columns*sizeof(rgba));
	}
	//library call to write the image out 
	 if(lodepng_encode32_file(filename, p->image, p->imageWidth, p->imageHeight)){
 		fprintf(stderr,"error %u: %s\n", error, lodepng_error_text(error));
 		return 1;
	}
	return 0;
}	 

int pixMap_rotate(pixMap *p,float theta){
	pixMap *oldPixMap=pixMap_copy(p);
	if(!oldPixMap)return 1;
 const float ox=p->imageWidth/2.0f;
 const float oy=p->imageHeight/2.0f;
 const float s=sin(degreesToRadians(-theta));
	const float c=cos(degreesToRadians(-theta));
	for(int y=0;y<p->imageHeight;y++){
		for(int x=0;x<p->imageWidth;x++){ 
   float rotx = c*(x-ox) - s * (oy-y) + ox;
   float roty = -(s*(x-ox) + c * (oy-y) - oy);
		 int rotj=rotx+.5;
		 int roti=roty+.5; 
		 if(roti >=0 && roti < oldPixMap->imageHeight && rotj >=0 && rotj < oldPixMap->imageWidth){
			 if(p->arrayType==0) memcpy(p->pixArray_arrays[y]+x,oldPixMap->pixArray_arrays[roti]+rotj,sizeof(rgba));
			 else if(p->arrayType==1) memcpy(p->pixArray_blocks[y]+x,oldPixMap->pixArray_blocks[roti]+rotj,sizeof(rgba));
			 else if(p->arrayType==2) memcpy(p->pixArray_overlay[y]+x,oldPixMap->pixArray_overlay[roti]+rotj,sizeof(rgba));			 
			}
			else{
				if(p->arrayType==0) memset(p->pixArray_arrays[y]+x,0,sizeof(rgba));
			 else if(p->arrayType==1) memset(p->pixArray_blocks[y]+x,0,sizeof(rgba));
			 else if(p->arrayType==2) memset(p->pixArray_overlay[y]+x,0,sizeof(rgba));		
			}		
		}	
	}
 pixMap_destroy(&oldPixMap);
 return 0;
}

pixMap *pixMap_copy(pixMap *p){
	pixMap *new=pixMap_init(p->arrayType);
	int rows = p->imageHeight;
	int columns = p->imageWidth;
	//allocate memory for new image of the same size as p->image and copy the image
	new->image = malloc(sizeof(p->image));
	//allocate memory and copy the arrays.
	new->pixArray_blocks = malloc(rows*sizeof(rgba));
	new->pixArray_overlay = malloc(rows*sizeof(rgba));

	if (new->arrayType == 0){
		new -> image = malloc(rows*sizeof(rgba[MAXWIDTH]));
		for(int i=0; i<rows; i++)
			memcpy(&new->pixArray_arrays[i], &p->pixArray_arrays[i], sizeof(rows*sizeof(rgba[MAXWIDTH])));
	}	
 	else if (new->arrayType == 1){
 		new -> pixArray_blocks = malloc(rows*MAXWIDTH*sizeof(rgba));
		for(int i=0; i<rows; i++)
			memcpy(&new->pixArray_blocks[i], &p->pixArray_blocks[i], sizeof(rows*columns*sizeof(rgba)));
	}
	else if (new->arrayType == 2){
		p -> pixArray_overlay = malloc(rows*sizeof(rgba));
		for(int i=0; i<rows; i++)
			memcpy(&new->pixArray_overlay[i], &p->pixArray_overlay[i], sizeof(rows*columns*sizeof(rgba)));
	}
	return new;
}