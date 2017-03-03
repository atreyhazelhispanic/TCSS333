//command line parsing 
int main(int arc, char *argv[]){
	//argc includes the program name
	//redirects and pipes are not included <input> output |
	//parsing remember convert your strings to integer and float atoi atof sscanf
	int i=1;
	while(i<argc){
	//check argv[i]
	i++; //increment the counter sometimes more than just +1
	}
	//do something 
	return 0;
}

//strings
//is the string writable - is a literal?
//does it have it's own memory allocated - is it a pointer copy
//is it propertly terminated

//join strings
//str(n)cat)
//must have enough room in final string, first string has to be terminated
//return value is a pointer to final string
//check what return value is in strncat

char a[20]="Hello ";   //need to make big enough, but not on a literal becuase of brackets
char b[]="World";
a=strcat(a,b);
//Hello World is in a
//strcpy does not need the first string to be terminated but strlen does need a terminator '\0'
strcpy(&(a[strlen(a)]),b);   //or
strcpy(a+strlen(a),b);

//sprintf
sprintf(c,"%.6s %s", a, b);

//memcpy - remember to add \0 at end or copy a \0 -- which is why there is a +1
memcpy(a+strlen(a),b,strlen(a)+strlen(b)+1);

//strcpy to a deep copy - can do a pointer copy with - also initialize with a[]="Hello "
//is actually a copy but char *a="Hello " is a pointer copy of a literal
//remember to use strcmp to do comparison (can't use <,>, ==) they will compare pointers.

//substring - you put \0 at the end and start at the index of the beginning
//substr(a,start,len);
a[start+len]='\0';
a[start]; //my stubstring

//file I/O
//reading files basic skeleton
FILE *ifp=fopen("filename", "r");
if(!ifp) return1;
//line by line
while(fgets(line, sizeof(line), ifp)){

}
fclose(ifp);

//binary or chunk by chunk
while(fread(&chunk,sizeof(chunk),1,ifp)){


}

//for text manipulation of fields - use sscanf or strtok
while(fgets(line,sizeof(line),ifp)){
	char *token=strtok(line," \n\t");
	while(token){
		//code goes here
		token=strtok(0," \n\t");
	}
	fclose(ifp);
}
fclose(fp);
//or
while(fgets(line,sizeof(line),ifp)){
	//remember that if needs to write to a block of memory -> need a pointer
	//returns the nubmer of paramerters that are correctly parsed
	if(sscanf(line,%d %s, &intVar, strVar) == 1){
		//do something
	}
}
fclose(fp);

//writing things out - for strings use fprintf, could use fputs for lines
//for binary or chunks of text use fwrite - most of the time you cand od it in the same loop and save yourself allocating an array

//2-d arrays  --> 3 types
//think of this as a 1-d array of different type
myfunc1(int array[1][3]);
myfunc2 (int array[2][3]);
myfunc3(int (*array)[3]);

int a[2][3]; //array of int[3]
int (*b)[3]; //this is a pointer to int[3]

b=malloc(sizeof(int[3])*nRows); //can only malloc the first dimension
if(b) free(b);

//pointer to blocks 
int **a;
//malloc room for the row pointers
a=malloc(sizeof(void *)*nRows);
for(int i=1;i<nRows;i++){
	if(a && a[i]) free(a[i]);
	if(a) free(a);
}

b=malloc(sizeof((int)*nRows*nCols));
for(int i=1;i<nCols;i++){
	if(b && b[i]) free(b[i]);
	if(b) free(b);
}

//structs how to init/copy and free

vector* vector_init(){
	//malloc the struct
	vector *v=malloc(sizeof(vector));
	//set everything to zero

	return v;
}
vector* vector_copy(){
	//malloc or use into to get object
	vector *vcpy=vector_init();
	*vcpy=v;
	//go through and do your mallocs and assign pointers to the right for things like pointers to a block
	return vcpy;
}

void vector_destroy(vector **v){
	//free all your mallocs from *v
	//then free *v and set to zero
	if(v && *v) free(*v);
	*v=0;
}

//bit manipulations - use unsigned variables (signed int is implementation dependent)
//when shifting it's important to put parenthesis around your number of bits to shift
//things fall off the cliff and don't come back
//AND & is used for masks
//OR | is used to combine
//XOR ^ is used to flip

//endianism
//when you look at a multibyte variable on ebyte at a time
int i=4;
char c[4] = (char*) &i;
//char[4] will print out with bytes reverse - char[0] is 4
000 0100 0000 0000 0000 0000 0000 0000
//Otherwise you can pretty much ignore for bit manipulation

//function pointers
int myfunc f(int a, float *b);
int a;
float b;
int (*fptr)(int,float*) = &myfunc;
int myValues = (fptr)(a,b);

//qsort
compfunc(const void *a, const void *b);
//watch out for strings must pass a ** so that strcmp can be called properly