#include "pixutils.h"
#include "bmp/bmp.h"

//private methods -> make static
static pixMap* pixMap_init();
static pixMap* pixMap_copy(pixMap *p);

//plugin methods <-new for Assignment 4;
static void rotate(pixMap *p, pixMap *oldPixMap,int i, int j,void *data);
static void convolution(pixMap *p, pixMap *oldPixMap,int i, int j,void *data);
static void flipVertical(pixMap *p, pixMap *oldPixMap,int i, int j,void *data);
static void flipHorizontal(pixMap *p, pixMap *oldPixMap,int i, int j,void *data);

static pixMap* pixMap_init(){
	pixMap *p=malloc(sizeof(pixMap));
	p->pixArray_overlay=0;
	return p;
}	

void pixMap_destroy (pixMap **p){
	if(!p || !*p) return;
	pixMap *this_p=*p;
	if(this_p->pixArray_overlay)
		free(this_p->pixArray_overlay);
	if(this_p->image)free(this_p->image);	
		free(this_p);
	this_p=0;
}
	
pixMap *pixMap_read(char *filename){
	pixMap *p=pixMap_init();
 	int error;
	if((error=lodepng_decode32_file(&(p->image), &(p->imageWidth), &(p->imageHeight),filename))){
 		fprintf(stderr,"error %u: %s\n", error, lodepng_error_text(error));
  		return 0;
	}
	p->pixArray_overlay=malloc(p->imageHeight*sizeof(rgba*));
	p->pixArray_overlay[0]=(rgba*) p->image;
	for(int i=1;i<p->imageHeight;i++){
  		p->pixArray_overlay[i]=p->pixArray_overlay[i-1]+p->imageWidth;
	}			
	return p;
}
int pixMap_write(pixMap *p,char *filename){
	int error=0;
if(lodepng_encode32_file(filename, p->image, p->imageWidth, p->imageHeight)){
  	fprintf(stderr,"error %u: %s\n", error, lodepng_error_text(error));
  	return 1;
}
	return 0;
}	 

pixMap *pixMap_copy(pixMap *p){
	pixMap *new=pixMap_init();
	*new=*p;
	new->image=malloc(new->imageHeight*new->imageWidth*sizeof(rgba));
	memcpy(new->image,p->image,p->imageHeight*p->imageWidth*sizeof(rgba));	
	new->pixArray_overlay=malloc(new->imageHeight*sizeof(void*));
	new->pixArray_overlay[0]=(rgba*) new->image;
	for(int i=1;i<new->imageHeight;i++){
  		new->pixArray_overlay[i]=new->pixArray_overlay[i-1]+new->imageWidth;
	}	
	return new;
}

	
void pixMap_apply_plugin(pixMap *p,plugin *plug){
	pixMap *copy=pixMap_copy(p);
	for(int i=0;i<p->imageHeight;i++){
		for(int j=0;j<p->imageWidth;j++){
			plug->function(p,copy,i,j,plug->data);
		}
	}
	pixMap_destroy(&copy);
}

int pixMap_write_bmp16(pixMap *p,char *filename){
	BMP16map *bmp16=BMP16map_init(p->imageHeight,p->imageWidth,0,5,6,5); //initialize the bmp type
	if(!bmp16) return 1;
	//bmp16->pixArray[i][j] is 2-d array for bmp files. It is analogous to the one for our png file pixMaps except that it is 16 bits 
	//However pixMap and BMP16_map are "upside down" relative to each other
 	//need to flip one of the the row indices when copying
 	rgba pixel = {0,0,0,0}; //16bit only has RGB -- need to downsample from 32bit
 	uint16_t pix16 = 0;
 	uint16_t r16 = 0;
 	uint16_t g16 = 0;
 	uint16_t b16 = 0;
 	uint16_t a16 = 0;

 	for(int i=0; i < p->imageHeight; i++){
 		for(int j=0; j < p->imageWidth; j++){
 			// pixel = p->pixArray_overlay[i][j];
 			pixel = p->pixArray_overlay[(p->imageHeight)-1-i][j]; //fliping the row indices while copying
 			r16 = pixel.r;
 			g16 = pixel.g;
 			b16 = pixel.b;
 			a16 = pixel.a;
 			
 			//using shifts to push 1's of the edge and zero them
 			//00000000 RRRRrrrr
			//00000000 0000RRRR >> 4
 			//RRRR0000 00000000 << 12
 
 			//using a mask to select the bits
 			//00000000 RRRRrrrr
 			// &
 			//00000000 11110000
 			//gives
 			//00000000 RRRR0000
 			//RRRR0000 00000000 << 8

 			//r16= 00000000 RRRRRrrr
			//g16=00000000 GGGGGGgg
			//b16=00000000 BBBBBbbb
 			//to  bmp16->pixMap[i][j]=RRRRRGGG GGGBBBBB

 			a16 = (b16 & 0xF0);
 			r16 = (r16 & 0xF0) >> 3;
	 		g16 = (g16 & 0xF0) >> 2;
 			b16 = (a16 & 0xF0) >> 3;
 			//-----------------------
 			a16 = (b16 & 0xF0) << 8;
 			r16 = (r16 & 0xF0) << 11;
	 		g16 = (g16 & 0xF0) << 10;
 			b16 = (a16 & 0xF0) << 8;

			pix16 = r16 | g16| b16 | a16;
			bmp16->pixArray[i][j] = pix16;
 		}
 	}

	BMP16map_write(bmp16,filename);
	BMP16map_destroy(&bmp16);
	return 0;
}	 
void plugin_destroy(plugin **plug){
 	//free the allocated memory and set *plug to zero (NULL)
	if((**plug).data) free((**plug).data);
	if(*plug) free(*plug);
}

plugin *plugin_parse(char *argv[] ,int *iptr){
	//malloc new plugin
	plugin *new=malloc(sizeof(plugin));
	new->function=0;
	new->data=0;
	
	int i=*iptr;
	if(!strcmp(argv[i]+2,"rotate")){
		new->function = rotate;
		new->data = malloc(2*sizeof(float));
		float theta = atof(argv[i+1]);  
		memcpy(new->data, &theta, sizeof(float));
		((float *) new->data)[0] = sin(degreesToRadians(-theta));
		((float *) new->data)[1] = cos(degreesToRadians(-theta));
		
		*iptr=i+2;  //needs to enter 1 more value for a parameter/value then moves 2 to get past it
		return new;	
	}	
	if(!strcmp(argv[i]+2,"convolution")){
	  	new->function = convolution;
	  	new->data = (int *)malloc(9*sizeof(int));

	  	for(int j=0; j<9; j++){
	  		((int *) new->data)[j] = atoi(argv[i+1+j]);
	  	}
		*iptr=i+10;	// needs to enter 9 integers that will be the 3x3 matrix
  		return new;
	}
	if(!strcmp(argv[i]+2,"flipHorizontal")){
		//We don't use the *data pointer, so no value/parameter expected
		new->function = flipHorizontal;
  		*iptr=i+1;
  		return new;
	}
	if(!strcmp(argv[i]+2,"flipVertical")){
		new->function = flipVertical;
  		*iptr=i+1; //no paramerters needed moves 1 past
  		return new;
	}		
	return(0);
}	

//define plugin functions
static void rotate(pixMap *p, pixMap *oldPixMap, int i, int j, void *data){
	float *sc = (float*) data;
	const float ox = p-> imageWidth/2.0f;
	const float oy = p->imageHeight/2.0f;
	const float s = sc[0];
	const float c = sc[1];
	const int y = i;
	const int x = j;
	float rotx = c*(x-ox) - s*(oy-y) + ox;
	float roty = -(s*(x-ox) + c*(oy-y) - oy);
	int rotj = rotx + .5;
	int roti = roty + .5;
	if(roti >=0 && roti <oldPixMap->imageHeight && rotj >=0 && rotj <oldPixMap->imageWidth){
		memcpy(p->pixArray_overlay[y]+x, oldPixMap->pixArray_overlay[roti]+rotj, sizeof(rgba));
	}else{
		memset(p->pixArray_overlay[y]+x, 0, sizeof(rgba)); // this sets the values at rows y -> x to 0
	}
}

static void convolution(pixMap *p, pixMap *oldPixMap,int i, int j,void *data){
	//implement algorithm given in https://en.wikipedia.org/wiki/Kernel_(image_processing)
	//assume that the kernel is a 3x3 matrix of integers
	//don't forget to normalize by dividing by the sum of all the elements in the matrix
	int n = 3; //for different kernel/mask just change n for NxN matrix
	int padding = n/2;
	int width = oldPixMap->imageWidth;
	int height = oldPixMap->imageHeight;
	int normalize = 0; //Divide each element in the kernel by this sum
	int r,g,b,a = 0;

	int kernel[n][n];
	int counter = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			normalize += kernel[i][j] = ((int *)data)[counter];
			counter ++;
		}// taking the array of 9 integers in data and puttin them into a 3x3 kernel
	}

	for(int kernelY=0; kernelY<n; kernelY++){
		for(int kernelX=0; kernelX<n; kernelX++){
			int theKern = kernel[kernelY][kernelX];
			int theX = (j-padding+kernelX+width)%width;
  			int theY = (i-padding+kernelY+height)%height; 
  			rgba thePixel = ((rgba**) oldPixMap->pixArray_overlay)[theX][theY];

  			//extend for edges
  			if(theX<0) theX=0;
  			if(theX>width-1) theX=width-1;
  			if(theY<0) theY=0;
  			if(theY>height-1) theY=height-1;

  			//Increment the summation, from the product of current image - pixel->r,g,b, or a    value, and kernel value @ position
  			r += (thePixel.r*theKern);
  			g += (thePixel.g*theKern);
  			b += (thePixel.b*theKern);
  			a += (thePixel.a*theKern);
		}
	}

	//Normalize the pixel @ (i,j) if != 0
	if(normalize != 0){
		r = r/normalize;
		g = g/normalize;
		b = b/normalize;
		a = a/normalize;
	}
	//Set new pixel values onto p
	((rgba**) p->pixArray_overlay)[i][j].r = r;
	((rgba**) p->pixArray_overlay)[i][j].g = g;
	((rgba**) p->pixArray_overlay)[i][j].b = b;
	((rgba**) p->pixArray_overlay)[i][j].a = a;
	//Dont't need to free kernel since it's a data structure defined with size... no pointer, no malloc
}

//very simple functions - does not use the data pointer - good place to start 
static void flipVertical(pixMap *p, pixMap *oldPixMap,int i, int j,void *data){
	memcpy(p->pixArray_overlay[i]+j, oldPixMap->pixArray_overlay[oldPixMap->imageHeight-1-i]+j, sizeof(rgba));
}	 
static void flipHorizontal(pixMap *p, pixMap *oldPixMap,int i, int j,void *data){
	memcpy(p->pixArray_overlay[i]+j, p->pixArray_overlay[i]+oldPixMap->imageWidth-1-j, sizeof(rgba));
}