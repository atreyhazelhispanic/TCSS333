#ifndef VECTORS_H
#define VECTORS_H

typedef struct {
	float x, y , z, length;
 //enter definition for float fields for x,y,z,length
} vector;

//header for vector_init fucniton
vector vector_init(float x, float y, float z);
//header for vector_add function, 
vector vector_add(vector alpha, vector beta);
//vector_dot function, 
float vector_dot(vector alpha, vector beta);
//vector_normalize function 
int vector_normalize(vector *alpha);
//and vector_print function
void vector_print(vector alpha);
#endif //VECTORS_H