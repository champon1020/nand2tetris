#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sub.h"
#include "parser.h"
#include "code.h"
#include "symbol.h"
#include "map.h"

char *commandType();
char *parseCommand();
char *outputFileName(char *fname);


int main(int argc, char *argv[]) {
  FILE *fp, *ofp;

  if(argc != 2) {
	printf("No asm files selected\n");
	exit(1);
  }

  if((fp = fopen(argv[1], "r")) == NULL){
	printf("Cannot open the file");
	exit(1);
  }

  if((ofp = fopen("out.hack", "w")) == NULL) {
	printf("Cannot open the output file");
	exit(1);
  }

  while(fgets(buf, sizeof(buf), fp) != NULL) {
	memset(cmd, '\0', sizeof(cmd));
	parseCommand();
	if(cmd[0] == '\0')
	  continue;

	//printf("%s", cmd);
	//printf("type: %s\n", commandType(cmd));
	if(!strcmp(commandType(cmd), "C_COMMAND")) {
	  char *dest = destMnemonic();
	  char *comp = compMnemonic();
	  char *jump = jumpMnemonic();
	  fprintf(ofp, "111%s%s%s\n", convertComp(comp), convertDest(dest), convertJump(jump));
	  //printf("dest: %s, comp: %s, jump: %s\n", destMnemonic(), compMnemonic(), jumpMnemonic());
	  //printf("dest: %s, comp: %s, jump: %s\n", convertDest(destMnemonic()), convertComp(compMnemonic()), convertJump(jumpMnemonic()));
	}else{
	  char *bin;
	  if((bin = convertBin(symbol())) != NULL)
		fprintf(ofp, "%s\n", bin);
	  else{
	  }
	}
  }

  printf("Complete!\n");

  fclose(fp);
  fclose(ofp);
  return 0;
}

char *parseCommand() {
  int cur = 0;
  int len = strlen(buf);
  while(cur < len && isspace(buf[cur])) {
	cur++;
  }
  int i = 0;
  while(cur < len) {
	if(buf[cur] != '\n' && isspace(buf[cur])){
	  cur++;
	  continue;
	}
	if(buf[cur] == '/' && buf[cur+1] == '/') {
	  cmd[i++] = '\n';
	  break;
	}
	cmd[i++] = buf[cur++];
  }
  if(cmd[0] == '\n') cmd[0] = '\0';
  return cmd;
}

char *outputFileName(char *fname) {
  int cur = 0;
  char *output = malloc(1024);
  while(cur < strlen(fname) && fname[cur] != '.')
	output[cur] = fname[cur++];
  strcat(output, ".hack");
  return output;
}
