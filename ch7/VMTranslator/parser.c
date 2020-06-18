#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "sub.h"

// strSegment returns string segment with selected number.
char *strSegment(char *s, int num){
  char *res = malloc(sizeof(s));
  int cur = 0, pos = 0, spcnt = 0;
  while(cur < strlen(s)){
	if(isspace(s[cur])){
	  if(spcnt++ == num) break;
	  ++cur;
	  continue;
	}
	if(spcnt == num){
	  res[pos++] = s[cur];
	}
	++cur;
  }
  
  if(spcnt < num) return NULL;
  return res;
}

char *arthmeticCommands[] = {"add", "sub", "neg", "eq", "gt", "lt", "and", "or", "not"};

char *commandType() {
  char *firSeg = strSegment(cmd, 0);

  // ARTHMETIC
  int judge = 0;
  for(int i=0; i<sizeof(arthmeticCommands)/sizeof(char*); i++){
	judge = judge || !strcmp(firSeg, arthmeticCommands[i]);
  }
  if(judge)
	return "C_ARTHMETIC";

  // PUSH
  if(!strcmp(firSeg, "push"))
	 return "C_PUSH";

  // POP
  if(!strcmp(firSeg, "pop"))
	return "C_POP";
  
  // LABEL
  if(!strcmp(firSeg, "lable"))
	return "C_LABEL";

  // FUNCTION
  if(!strcmp(firSeg, "function"))
	return "C_FUNCTION";

  // RETURN
  if(!strcmp(firSeg, "return"))
	return "C_RETURN";
  
  // CALL
  if(!strcmp(firSeg, "call"))
	return "C_CALL";

  printf("Command is not defined\n");
  exit(1);
}

char *arg0() {
  return strSegment(cmd, 0);
}

char *arg1() {
  return strSegment(cmd, 1);
}

char *arg2() {
  return strSegment(cmd, 2);
}
