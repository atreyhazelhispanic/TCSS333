#include <math.h>
#include <stdio.h>
#include "vectors.h"

//vector init function
vector vector_init(float x, float y, float z){
 vector v;
 v.x=x;
 v.y=y;
 v.z=z;
 v.length=sqrt(x*x+y*y+z*z);
	return v;
}
//write vector_add function that takes two vectors as parameters and returns a vector that is the sum of the two vectors
vector vector_add(vector alpha, vector beta){
	return vector_init(alpha.x+beta.x,alpha.y+beta.y,alpha.z+beta.z);
}
//write vector_dot function that takes two vectors as parameters and returns a float which is the dot product (look it up if you don't know what a dot product is)
float vector_dot(vector alpha, vector beta){
	return (alpha.x*beta.x)+(alpha.y*beta.y)+(alpha.z*beta.z);
}

//write vector_normalize function that takes a pointer to a vector as a parameter and modify the vector by dividing each of the x,y,z components by its length. Check if the length is zero and return 1 if it is zero (unsuccessful normalization) , otherwise return 0 (successful normalization)
int vector_normalize(vector *alpha){
	if(alpha->length == 0){
		return 1;
	}else{
		alpha->x = alpha->x/alpha->length;
		alpha->y = alpha->y/alpha->length;
		alpha->z = alpha->z/alpha->length;
		return 0;
	}
}

//write vector_print function that prints out the x,y,z and length of a vector on separate lines
void vector_print(vector alpha){
	printf("\"x\" value is:%f \n", alpha.x);
	printf("\"y\" value is:%f \n", alpha.y);
	printf("\"z\" value is:%f \n", alpha.z);
	printf("\"length\" value is:%f \n", alpha.length);
}
