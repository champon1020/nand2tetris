#include <string.h>
#include <stdlib.h>
#include "sub.h"

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
  if(strchr(mnemonic, '0'))
	return "0101010";
  if(strchr(mnemonic, '0'))
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
