#include <stdio.h>
#include <string.h>

FILE *ofp;

void setFileName(char *fileName){
  char *outputFileName = malloc(sizeof(fileName) + 10);
  int cur = 0; pos = 0;
  while(cur < strlen(fileName))
	outputFileName[pos++] = fileName[cur++];

  cur = 0;
  char *extend = ".asm";
  while(cur < strlen(extend))
	outputFileName[pos++] = extend[cur++];

  if((ofp = fopen(outputFileName, "w")) == NULL){
	printf("Cannot open output file %s\n", outputFileName);
	exit(1);
  }
}

void writeArthmetic(char *cmd){
  
}

void writePushPop(char *cmd, char *seg, int index){
}
