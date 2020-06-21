#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "sub.h"
#include "parser.h"
#include "code_writer.h"

char buf[4096];

char *basename(char *p){
  int cur = 0, slcnt = 0;
  while(cur < strlen(p)){
    if(p[cur++] == '/') slcnt++;
  }
  
  cur = 0;
  int pos = 0;
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
  int cur = 0, slcnt = 0;
  while(cur < strlen(p)){
    if(p[cur++] == '/') slcnt++;
  }

  cur = 0;
  int pos = 0;
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

void parseCommand(){
  int cur = 0, len = strlen(buf);

  // Remove prefix spaces
  while(cur < len && isspace(buf[cur])) cur++;

  int pos = 0;
  while(cur < len && buf[cur] != '\n'){
    if(buf[cur] == '/' && buf[cur+1] == '/'){
      cmd[pos] = '\0';
      break;
	}
    cmd[pos++] = buf[cur++];
  }
}

char *oFileName(char *dirname){
  char *outputFileName = malloc(2048);
  int cur = 0, pos = 0;
  while(cur < strlen(dirname)){
    outputFileName[pos++] = dirname[cur++];
  }

  outputFileName[pos++] = '/';
  
  char *base = basename(dirname);
  cur = 0;
  while(cur < strlen(base)){
    outputFileName[pos++] = base[cur++];
  }
  
  cur = 0;
  char *extend = ".asm";
  while(cur < strlen(extend)){
    outputFileName[pos++] = extend[cur++];
  }
  
  return outputFileName;
}

void *extention(char *ext, char *p){
  int len = strlen(p);
  if(len >= 3){
    ext[0] = p[len-3];
    ext[1] = p[len-2];
    ext[2] = p[len-1];
  }
}

void process(char *fileName) {
  FILE *fp;
  
  if((fp = fopen(fileName, "r")) == NULL){
    printf("Cannot open file '%s'\n", fileName);
    exit(1);
  }

  currentBaseName = basename(fileName);

  while(fgets(buf, sizeof(buf), fp) != NULL){
    memset(cmd, '\0', sizeof(cmd));
    parseCommand();
    if(cmd[0] == '\0')
      continue;

    char *cmdType = commandType();
    char *arg1_ = arg1();
    char *arg2_ = arg2();
    printf("Command-Type: %-15s arg1: %-15s arg2: %-15s\n", cmdType, arg1_, arg2_);

    if(!strcmp(cmdType, "C_ARTHMETIC")){
      writeArthmetic(arg0());
    }else if(!strcmp(cmdType, "C_PUSH") || !strcmp(cmdType, "C_POP")){
      writePushPop(arg0(), arg1_, atoi(arg2_));
    }else if(!strcmp(cmdType, "C_LABEL")){
	  writeLabel(arg1());
	}else if(!strcmp(cmdType, "C_IF")){
	  writeIf(arg1());
	}else if(!strcmp(cmdType, "C_GOTO")){
	  writeGoto(arg1());
	}else if(!strcmp(cmdType, "C_FUNCTION")){
	  writeFunction(arg1_, atoi(arg2_));
	}else if(!strcmp(cmdType, "C_RETURN")){
	  writeReturn();
	}else if(!strcmp(cmdType, "C_CALL")){
	  writeCall(arg1_, atoi(arg2_));
	}else{
	  printf("Command is not defined: %s\n", cmdType);
	}
  }

  fclose(fp);
}

int main(int argc, char *argv[]) {
  if(argc != 2){
    printf("No vm files selected\n");
    exit(1);
  }

  char *fileName = argv[1];
  char *outputFileName = oFileName(dirname(fileName));

  initialize();
  if((ofp = fopen(outputFileName, "w")) == NULL){
    printf("Cannot open output file %s\n", outputFileName);
    exit(1);
  }

  writeInit();
  char ext[3];
  int len = strlen(fileName);
  extention(ext, fileName);
  if(len >= 3 && !strcmp(ext, ".vm")){
	printf("Process file\n");
    process(fileName);
  }else{
    printf("Process directory\n");
	DIR *dir;
	struct dirent *dp;
	if((dir = opendir(fileName)) == NULL){
	  printf("Cannot open dir\n");
	  exit(1);
	}

	char *buf = malloc(2048*sizeof(char *));
	for(dp = readdir(dir); dp != NULL; dp=readdir(dir)){
	  printf("FILE: %s\n", dp->d_name);
	  extention(ext, dp->d_name);
	  if(!strcmp(ext, ".vm")){
		sprintf(buf, "%s%s", fileName, dp->d_name);
		process(buf);
	  }else{
		printf("pass\n");
	  }
	}
	free(buf);
  }
  fprintf(ofp, "(END)\n@END\n0;JMP\n");

  printf("Complete!\n");
  printf("Output at %s\n", outputFileName);

  fclose(ofp);

  return 0;
}
