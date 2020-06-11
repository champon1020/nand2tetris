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
  if(!strcmp(mnemonic, "0"))
	return "0101010";
  if(!strcmp(mnemonic, "1"))
	return "0111111";
  if(!strcmp(mnemonic, "-1"))
	return "0111010";
  if(!strcmp(mnemonic, "D"))
	return "0001100";
  if(!strcmp(mnemonic, "A"))
	return "0110000";
  if(!strcmp(mnemonic, "M"))
	return "1110000";
  if(!strcmp(mnemonic, "!D"))
	return "0001101";
  if(!strcmp(mnemonic, "!A"))
	return "0110001";
  if(!strcmp(mnemonic, "!M"))
	return "1110001";
  if(!strcmp(mnemonic, "-D"))
	return "0001111";
  if(!strcmp(mnemonic, "-A"))
	return "0110011";
  if(!strcmp(mnemonic, "-M"))
	return "1110011";
  if(!strcmp(mnemonic, "D+1"))
	return "0011111";
  if(!strcmp(mnemonic, "A+1"))
	return "0110111";
  if(!strcmp(mnemonic, "M+1"))
	return "1110111";
  if(!strcmp(mnemonic, "D-1"))
	return "0001110";
  if(!strcmp(mnemonic, "A-1"))
	return "0110010";
  if(!strcmp(mnemonic, "M-1"))
	return "1110010";
  if(!strcmp(mnemonic, "D+A"))
	return "0000010";
  if(!strcmp(mnemonic, "D+M"))
	return "1000010";
  if(!strcmp(mnemonic, "D-A"))
	return "0010011";
  if(!strcmp(mnemonic, "D-M"))
	return "1010011";
  if(!strcmp(mnemonic, "A-D"))
	return "0000111";
  if(!strcmp(mnemonic, "M-D"))
	return "1000111";
  if(!strcmp(mnemonic, "D&A"))
	return "0000000";
  if(!strcmp(mnemonic, "D&M"))
	return "1000000";
  if(!strcmp(mnemonic, "D|A"))
	return "0010101";
  if(!strcmp(mnemonic, "D|M"))
	return "1010101";
  return "101010";
}

char *convertJump(char *mnemonic) {
  if(mnemonic == NULL)
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
  return "000";
}
