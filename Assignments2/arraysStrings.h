#ifndef Array_Strings
#define Array_Strings
#include "vectors.h"
//fill in the parameters and return type
char* joinrev(char alpha[], char* beta);
void* joinrev_generic(void* alpha, void* beta, size_t size, size_t nmembA, size_t nmembB);
int readTextAddBinary(char* fileIn, char* fileOut);
int readBinaryNormText(char* fileIn, char* fileOut);
/*wc();*/
#endif //Array_Strings