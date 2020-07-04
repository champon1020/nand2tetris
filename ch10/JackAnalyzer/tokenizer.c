#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "sub.h"

void initTokenizer();
bool hasMoreToken();
bool checkSymbol(char c);
bool checkKeyword(char *s);
char *tokenType();

int commandCur = 0;

void initTokenizer(){
  commandCur = 0;
}

bool hasMoreToken() {
  return commandCur < strlen(cmd);
}

bool checkSymbol(char c){
  if(c == '{' ||
	 c == '}' ||
	 c == '(' ||
	 c == ')' ||
	 c == '[' ||
	 c == ']' ||
	 c == '.' ||
	 c == ',' ||
	 c == ';' ||
	 c == '+' ||
	 c == '-' ||
	 c == '*' ||
	 c == '/' ||
	 c == '&' ||
	 c == '|' ||
	 c == '<' ||
	 c == '>' ||
	 c == '=' ||
	 c == '~'){
	return true;
  }
  return false;
}

bool checkKeyword(char *s){
  if(!strcmp(s, "class") ||
	 !strcmp(s, "constructor") ||
	 !strcmp(s, "function") ||
	 !strcmp(s, "method") ||
	 !strcmp(s, "field") ||
	 !strcmp(s, "static") ||
	 !strcmp(s, "var") ||
	 !strcmp(s, "int") ||
	 !strcmp(s, "char") ||
	 !strcmp(s, "boolean") ||
	 !strcmp(s, "void") ||
	 !strcmp(s, "true") ||
	 !strcmp(s, "false") ||
	 !strcmp(s, "null") ||
	 !strcmp(s, "this") ||
	 !strcmp(s, "let") ||
	 !strcmp(s, "do") ||
	 !strcmp(s, "if") ||
	 !strcmp(s, "else") ||
	 !strcmp(s, "while") ||
	 !strcmp(s, "return")){
	return true;
  }
  return false;
}

bool checkIsNumber(char *s) {
  bool judge = true;
  int cur = 0;
  while(cur < strlen(s)){
	if(!isdigit(s[cur]))
	  judge = false;
	++cur;
  }
  return judge;
}

bool isStr = false;

char *tokenType() {
  int pos = 0, len = strlen(cmd);
  char tkn[4096];
  memset(tkn, '\0', sizeof(tkn));
  while(commandCur < len){
	if(cmd[commandCur] == '"'){
	  isStr = !isStr;
	  ++commandCur;
	  if(!isStr)
		return "STRING_CONST";
	  continue;
	}
	if(!isStr){
	  if(isspace(cmd[commandCur])){
	    ++commandCur;
		break;
	  }
	  if(checkSymbol(cmd[commandCur])){
		if(!pos){
		  ++commandCur;
		  return "SYMBOL";
		}else
		  break;
	  }
	}
	tkn[pos++] = cmd[commandCur++];
  }

  if(isspace(tkn[0]) || strlen(tkn) == 0)
	return "NULL";
  printf("%s ", tkn);

  if(checkKeyword(tkn))
	return "KEYWORD";
  else if(checkIsNumber(tkn))
	return "INT_CONST";
  else
	return "IDENTIFIER";
}

