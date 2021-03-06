#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>
#include "sub.h"
#include "tokenizer.h"
#include "compilationEngine.h"


void allocateString(char *src, char *org, int start){
  int cur = 0;
  while(cur < strlen(org)){
	src[start++] = org[cur++];
  }
}

char *basename(char *p){
  int cur = 0, slcnt = 0, pos = 0;
  while(cur < strlen(p)){
    if(p[cur++] == '/') slcnt++;
  }
  cur = 0;
  char *res = malloc(sizeof(p));
  while(cur < strlen(p)){
    if(p[cur] == '/'){
      --slcnt; ++cur;
      continue;
    }
    if(!slcnt){
      res[pos++] = p[cur];
    }
    ++cur;
  }
  return res;
}

char *dirname(char *p){
  int cur = 0, slcnt = 0, pos = 0;
  while(cur < strlen(p)){
    if(p[cur++] == '/') slcnt++;
  }
  cur = 0;
  char *res = malloc(sizeof(p)*sizeof(char *));
  while(cur < strlen(p)){
   if(p[cur] == '/'){
     --slcnt;
   }
   if(slcnt){
     res[pos++] = p[cur];
   }
   ++cur;
  }
  return res;
}

char *removeExtFromPath(char *p) {
  int cur = 0;
  char *base = basename(p);
  char *res = malloc(sizeof(base)*sizeof(char *));
  while(cur < strlen(base) && base[cur] != '.'){
	res[cur] = base[cur];
	cur++;
  }
  return res;
}

int endWith(char *str, char *suffix){
  char ext[5];
  int len = strlen(str);
  if(len < 5)
	return 0;

  for(int i=0; i<5; i++){
	ext[i] = str[len-(5-i)];
  }
  return !strcmp(ext, suffix);
}

void process(char *fileName){
  if((fp = fopen(fileName, "r")) == NULL){
	printf("Failed to open input file %s\n", fileName);
	exit(1);
  }

  EOF_ = 0;
  while(!EOF_){
	advance();
	char *tknType = tokenType();
	if(!strcmp(tknType, "NULL"))
	  continue;
	compileClass();
  }
}

int main(int argc, char *argv[]){
  if(argc != 2){
	printf("The number of arguments must be one, source name\n");
	exit(1);
  }

  char *fileName = argv[1];
  if(endWith(fileName, ".jack")){
	char *buf = malloc(sizeof(char *) * 100);
	char *buf2 = malloc(sizeof(char *) * 100);
	char *outputXmlName = malloc(sizeof(char *) * 100);
	char *outputVmName = malloc(sizeof(char *) * 100);
	sprintf(buf, "%s/%s.xml", dirname(fileName), removeExtFromPath(basename(fileName)));
	sprintf(buf2, "%s/%s.vm", dirname(fileName), removeExtFromPath(basename(fileName)));
	allocateString(outputXmlName, buf, 0);
	allocateString(outputVmName, buf2, 0);
	
	if((xmlOfp = fopen(outputXmlName, "w")) == NULL){
	  printf("Failed to open output XML file %s\n", outputXmlName);
	  exit(1);
	}
	if((vmOfp = fopen(outputVmName, "w")) == NULL){
	  printf("Failed to open output VM file %s\n", outputVmName);
	  exit(1);
	}

	process(fileName);
	printf("FILE: %s, XML: %s, VM: %s\n", fileName, outputXmlName, outputVmName);
  }else{
	DIR *dir;
	struct dirent *dp;
	if((dir = opendir(fileName)) == NULL){
	  printf("Failed to open input dir %s\n", fileName);
	  exit(1);
	}
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir)){  
	  char *buf = malloc(sizeof(char *) * 100);
	  char *buf2 = malloc(sizeof(char *) * 100);
	  char *outputXmlName = malloc(sizeof(char *) * 100);
	  char *outputVmName = malloc(sizeof(char *) * 100);
	  sprintf(buf, "%s/%s.xml", dirname(fileName), removeExtFromPath(basename(dp->d_name)));
	  sprintf(buf2, "%s/%s.vm", dirname(fileName), removeExtFromPath(basename(dp->d_name)));
	  allocateString(outputXmlName, buf, 0);
	  allocateString(outputVmName, buf2, 0);

	  if(endWith(dp->d_name, ".jack")){  
		if((xmlOfp = fopen(outputXmlName, "w")) == NULL){
		  printf("Failed to open output XML file %s\n", outputXmlName);
		  exit(1);
		}
		if((vmOfp = fopen(outputVmName, "w")) == NULL){
		  printf("Failed to open output VM file %s\n", outputVmName);
		  exit(1);
		}
		
		process(dp->d_name);
		printf("FILE: %-20s, OUTPUT: %-20s, VM: %-20s\n", dp->d_name, outputXmlName, outputVmName);
	  }
	}
  }
  return 0;
}
