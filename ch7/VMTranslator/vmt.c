#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sub.h"
#include "parser.h"

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
  char *res = malloc(sizeof(p));
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
  while(cur < len){
	if(buf[cur] == '/' && buf[cur+1] == '/'){
	  cmd[pos] = '\n';
	  break;
	}
	cmd[pos++] = buf[cur++];
  }

  if(cmd[0] == '\n') cmd[0] = '\0';
}

void process(char *fileName) {
  FILE *fp;
  
  if((fp = fopen(fileName, "r")) == NULL){
	printf("Cannot open file '%s'\n", fileName);
	exit(1);
  }
  
  while(fgets(buf, sizeof(buf), fp) != NULL){
	memset(cmd, '\0', sizeof(cmd));
	parseCommand();
	if(cmd[0] == '\0')
	  continue;

	printf("%s %s %s\n", commandType(), arg1(), arg2());
  }

  fclose(fp);
}

int main(int argc, char *argv[]) {
  if(argc != 2){
	printf("No vm files selected\n");
	exit(1);
  }

  if(strcspn(argv[1], ".vm") == strlen(argv[1])){
	printf("Process directory\n");

	// process files in the directory
  }else{
	printf("Process file\n");
	printf("dirname: %s, basename: %s\n", dirname(argv[1]), basename(argv[1]));

	// Process one file.
	process(argv[1]);
  }

  return 0;
}