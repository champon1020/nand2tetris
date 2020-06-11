#include <string.h>
#include <stdlib.h>
#include "sub.h"

char *commandType() {
  if(cmd[0] == '@') return  "A_COMMAND";
  else if(cmd[0] == '(') return "L_COMMAND";
  return "C_COMMAND";
}

char *destMnemonic() {
  if(strstr(cmd, "=") == NULL)
	return "";
  
  char *dest = malloc(1024);
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
  char *comp = malloc(1024);
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
  char *jump = malloc(1024);
  while(cur < strlen(cmd) && cmd[cur] != '\n'){
	jump[i++] = cmd[cur++];
  }
  return jump;
}
