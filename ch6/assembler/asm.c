#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *commandType();
char *parseCommand();
char *destMnemonic();
char *compMnemonic();
char *jumpMnemonic();
char *convertDest(char *mnemonic);
char *convertComp(char *mnemonic);
char *convertJump(char *mnemonic);

const int MNEM_MAX = 1024;
char buf[4096], cmd[4096];


int main(int argc, char *argv[]) {
  FILE *fp;

  if(argc != 2) {
	printf("No asm files selected\n");
	exit(1);
  }

  if((fp = fopen(argv[1], "r")) == NULL){
	printf("Cannot open the file");
	exit(1);
  }

  while(fgets(buf, sizeof(buf), fp) != NULL) {
	memset(cmd, '\0', sizeof(cmd));
	parseCommand();
	if(cmd[0] == '\0')
	  continue;

	printf("%s", cmd);
	if(commandType(cmd) == "C_COMMAND") {
	  printf("dest: %s, comp: %s, jump: %s\n", destMnemonic(), compMnemonic(), jumpMnemonic());
	  printf("dest: %s, comp: %s, jump: %s\n", convertDest(destMnemonic()), convertComp(compMnemonic()), convertJump(jumpMnemonic()));
	}
	//printf("type: %s\n", commandType(cmd));
  }

  fclose(fp);
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


// --------------------- parse module -------------------------

char *commandType() {
  if(cmd[0] == '@') return  "A_COMMAND";
  else if(cmd[0] == '(') return "L_COMMAND";
  return "C_COMMAND";
}

char *destMnemonic() {
  if(strstr(cmd, "=") == NULL)
	return "";
  
  char *dest = malloc(MNEM_MAX);
  int cur = 0;
  while(cur < strlen(cmd) && cmd[cur] != '='){
	dest[cur] = cmd[cur];
	cur++;
  }
  return dest;
}

char *compMnemonic() {
  int cur = 0;
  if(strstr(cmd, "=") != NULL) {
	while(cur < strlen(cmd) && cmd[cur] != '=') cur++;
	cur++;
  }
  
  int i = 0;
  char *comp = malloc(MNEM_MAX);
  while(cur < strlen(cmd) && cmd[cur] != ';' && cmd[cur] != '\n'){
	comp[i++] = cmd[cur++];
  }
  return comp;
}

char *jumpMnemonic() {
  if(strstr(cmd, ";") == NULL)
	return "";
  
  int cur = 0;
  while(cur < strlen(cmd) && cmd[cur] != ';')
	cur++;
  cur++;
  
  int i = 0;
  char *jump = malloc(MNEM_MAX);
  while(cur < strlen(cmd) && cmd[cur] != '\n'){
	jump[i++] = cmd[cur++];
  }
  return jump;
}


// --------------------- code module -------------------------

char *convertDest(char *mnemonic) {
  char *res = malloc(3);
  res[0] = '0'; res[1] = '0'; res[2] = '0';
  if(mnemonic == NULL)
	return res;

  if(strchr(mnemonic, 'A') != NULL)
	res[0] = '1';
  if(strchr(mnemonic, 'D') != NULL)
	res[1] = '1';
  if(strchr(mnemonic, 'M') != NULL)
	res[2] = '1';
  return res;
}

char *convertComp(char *mnemonic) {
  if(strchr(mnemonic, "0"))
	return "0101010";
  if(strchr(mnemonic, "1"))
	return "0111111";
  
}

char *convertJump(char *mnemonic) {
  if(mnemonic == "")
	return "000";
  if(!strcmp(mnemonic, "JGT"))
	return "001";
  if(!strcmp(mnemonic, "JEQ"))
	return "010";
  if(!strcmp(mnemonic, "JGE"))
	return "011";
  if(!strcmp(mnemonic, "JLT"))
	return "100";
  if(!strcmp(mnemonic, "JNE"))
	return "101";
  if(!strcmp(mnemonic, "JLE"))
	return "110";
  if(!strcmp(mnemonic, "JMP"))
	return "111";
  return "";
}
