#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "vectors.h"

char *joinrev(char *a,char *b);
void *joinrev_generic(void *a, void *b, int typeSize, int aElements, int bElements);
int readTextAddBinary(char *textFile, char *binFile);
int readBinaryNormText(char *binFile, char *textFile);
int readNormTextWriteNormBinaryFtell(char *textFile, char *binFile);
int readNormTextWriteNormBinaryRealloc(char *textFile, char *binFile);
int wc(char *textFile);