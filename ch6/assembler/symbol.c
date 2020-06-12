#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "map.h"
#include "sub.h"

char *fill(char *s, int size){
  char *res = malloc(sizeof(char)*size);
  int cur = 0;
  while(cur + strlen(s) < size)
	res[cur++] = '0';

  int i = 0;
  while(i < strlen(s))
	res[cur++] = s[i++];

  return res;
}

char *reverse(char *s) {
  char *res = malloc(sizeof(s));
  int cur = 0;
  while(cur < strlen(s)){
	res[cur] = s[strlen(s)-cur-1];
	cur++;
  }
  return res;
}

char *convertBin(char *symbol) {
  int cur = 0;
  int judge = 1;
  while(cur < strlen(symbol)){
	if(!isdigit(symbol[cur++]))
	  judge = 0;
  }

  if(!judge)
	return NULL;

  cur = 0;
  int n = atoi(symbol);
  char *buf = malloc(128);
  while(n > 0){
	buf[cur++] = (char)(n%2 + '0');
	n = n/2;
  }

  char *res = fill(reverse(buf), 16);
  return res;
}

void initSymbolMap(){
  insert("SP", "0000000000000000");
  insert("LCL", "0000000000000001");
  insert("ARG", "0000000000000010");
  insert("THIS", "0000000000000011");
  insert("THAT", "0000000000000100");
  insert("R0", "0000000000000000");
  insert("R1", "0000000000000001");
  insert("R2", "0000000000000010");
  insert("R3", "0000000000000011");
  insert("R4", "0000000000000100");
  insert("R5", "0000000000000101");
  insert("R6", "0000000000000110");
  insert("R7", "0000000000000111");
  insert("R8", "0000000000001000");
  insert("R9", "0000000000001001");
  insert("R10", "0000000000001010");
  insert("R11", "0000000000001011");
  insert("R12", "0000000000001100");
  insert("R13", "0000000000001101");
  insert("R14", "0000000000001110");
  insert("R15", "0000000000001111");
  insert("SCREEN", "0100000000000000");
  insert("KBD", "1000000000000000");
}
