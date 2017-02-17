#include "arraysStrings.h"

char *joinrev(char *a,char *b){
	const int alength=strlen(a),blength=strlen(b); 
	char *c=malloc(alength+blength+1); //need to make a copy in this case because joinrev must also work on literals
	if(!c)return 0; //check that malloc worked
	memcpy(c,a,alength);
	memcpy(c+alength,b,blength+1); //can use strcpy too
	char temp,*right,*left;
	left=c+alength;
	right=c+alength+blength-1;
	while(left <right){
	 temp=*right;
	 *right--=*left;
	 *left++=temp;
	}
	return c;
}

void *joinrev_generic(void *a, void *b, int typeSize, int aElements, int bElements){
 char *c=malloc((aElements+bElements)*typeSize); //make copy
	if(!c)return 0; //check that malloc worked
	memcpy(c,a,aElements*typeSize); //copy as in joinrev string edition
	memcpy(c+aElements*typeSize,b,bElements*typeSize); //in this case we can't use stcpy
 char temp[typeSize],*right,*left; //we need a temp variable for the swap
	left=c+aElements*typeSize;        
	right=c+(aElements+bElements-1)*typeSize;
	while(left <right){
	 memcpy(temp,right,typeSize);
	 memmove(right,left,typeSize);
	 right-=typeSize;
	 memcpy(left,temp,typeSize);
	 left+=typeSize;
	}
	return (void*) c;
}

int readTextAddBinary(char *textFile, char *binFile){
 FILE *infp=fopen(textFile,"r");
 if(!infp){
		fprintf(stderr,"unable to open input file %s\n",textFile);
		return 1;
	}
 FILE *outfp=fopen(binFile,"w");
 if(!outfp){
		fprintf(stderr,"unable to open output file %s\n",binFile);
		return 1;
	}
	char line[1024];
	while(fgets(line,sizeof(line),infp)){
		float x1,y1,z1,x2,y2,z2;
		if(sscanf(line,"%f %f %f %f %f %f",&x1,&y1,&z1,&x2,&y2,&z2) != 6)return 1;
		vector v=vector_init(x1+x2,y1+y2,z1+z2);
		if(!fwrite(&v,sizeof(v),1,outfp))return 1;
	}
	fclose(infp);
	fclose(outfp);
 return 0;	
}

int readBinaryNormText(char *binFile, char *textFile){
	FILE *infp=fopen(binFile,"r");
 if(!infp){
		fprintf(stderr,"unable to open input file %s\n",binFile);
		return 1;
	}
 FILE *outfp=fopen(textFile,"w");
 if(!outfp){
		fprintf(stderr,"unable to open output file %s\n",textFile);
		return 1;
	}
	vector v;
	while(fread(&v,sizeof(vector),1,infp)){
		vector_normalize(&v);
		fprintf(outfp,"%f\t%f\t%f\t%f\t",v.x,v.y,v.z,v.length);
	}		
	fclose(infp);
	fclose(outfp);
	return 0;
}
int readNormTextWriteNormBinaryFtell(char *textFile, char *binFile){
	FILE *infp=fopen(textFile,"r");
 if(!infp){
		fprintf(stderr,"unable to open input file %s\n",textFile);
		return 1;
	}
 FILE *outfp=fopen(binFile,"w");
 if(!outfp){
		fprintf(stderr,"unable to open output file %s\n",binFile);
		return 1;
	}
 fseek(infp,0,SEEK_END);
 int nSize=ftell(infp);
 rewind(infp);
 char *line=(char*) malloc((nSize+1));
 fread(line,nSize,1,infp);
 line[nSize]='\0';
 char *delim="\t\n";
 char *token=strtok(line,delim);
 while(token){
		vector v;
		v.x=atof(token);
		if(!(token=strtok(0,delim))){free(line);return 1;}
		v.y=atof(token);
		if(!(token=strtok(0,delim))){free(line);return 1;}
		v.z=atof(token);
		if(!(token=strtok(0,delim))){free(line);return 1;}
		v.length=atof(token);
		if(!fwrite(&v,sizeof(vector),1,outfp)){free(line);return 1;}
		token=strtok(0,delim);						
	}
		if(line)free(line);
	fclose(infp);
	fclose(outfp);
	return 0;
}

int readNormTextWriteNormBinaryRealloc(char *textFile, char *binFile){
	FILE *infp=fopen(textFile,"r");
 if(!infp){
		fprintf(stderr,"unable to open input file %s\n",textFile);
		return 1;
	}
 FILE *outfp=fopen(binFile,"w");
 if(!outfp){
		fprintf(stderr,"unable to open output file %s\n",binFile);
		return 1;
	}
	int lineSize=8,lineStrLen=0;
 char *line=(char*) malloc(lineSize);
 if(!line)return 1;
 int bytesRead=0;
 while ((bytesRead=fread(line+lineStrLen,1,lineSize-lineStrLen,infp)) == lineSize-lineStrLen){ //read in at most lineSize bytes
		//if byteRead is lineSize-lineStrLen - then we need more space
		lineStrLen=lineSize;
		lineSize*=2;
		line=realloc(line,lineSize);
		if(!line){fprintf(stderr,"unable to realloc more memory for line\n");return 1;}
	}
	//otherwise 
	line[lineStrLen+bytesRead]='\0';

 char *delim="\t\n";
 char *token=strtok(line,delim);
 while(token){
		vector v;
		v.x=atof(token);
		if(!(token=strtok(0,delim))){free(line);return 1;}
		v.y=atof(token);
		if(!(token=strtok(0,delim))){free(line);return 1;}
		v.z=atof(token);
		if(!(token=strtok(0,delim))){free(line);return 1;}
		v.length=atof(token);
		if(!fwrite(&v,sizeof(vector),1,outfp)){free(line);return 1;}
		token=strtok(0,delim);						
	}
	fclose(infp);
	fclose(outfp);
	if(line)free(line);
	return 0;
}

int wc(char *textFile){
	FILE *infp=fopen(textFile,"r");
 if(!infp){
		fprintf(stderr,"unable to open input file %s\n",textFile);
		return 1;
	}
	int inWord=0;
	int nLines=0,nWords=0,nChars=0;
	char c;
	while (fread(&c,1,1,infp)){
	 //find if change in status
	 if(isspace(c)){
			if(inWord){
				nWords++;
				inWord=0;
			}	
			if(c == '\n')nLines++;
		}
		else{
			inWord=1;
		}	
		nChars++;	
	}
	fclose(infp);
	//check for edge case
	if(inWord) nWords++;
	printf("   %d %d %d %s\n",nLines,nWords,nChars,textFile);
	return 0;
}