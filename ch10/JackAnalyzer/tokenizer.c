#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "sub.h"

void initTokenizer();
bool hasMoreToken();
bool checkSymbol(char c);
bool checkKeyword(char *s);
char *tokenType();
char *keyWord();

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
  memset(token, '\0', sizeof(token));
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
		  token[0] = cmd[commandCur++];
		  return "SYMBOL";
		}else
		  break;
	  }
	}
    token[pos++] = cmd[commandCur++];
  }

  if(isspace(token[0]) || strlen(token) == 0)
	return "NULL";

  if(checkKeyword(token))
	return "KEYWORD";
  else if(checkIsNumber(token))
	return "INT_CONST";
  else
	return "IDENTIFIER";
}

char *keyWord() {
  char keyword[128];
  int pos = 0, cur = 0, len = strlen(token);
  while(cur < len) {
	keyword[pos++] = toupper(token[cur++]);
  }
  return keyword;
}

char symbol() {
  return token[0];
}

char *identifier() {
  return token;
}

int intVal() {
  return atoi(token);
}

char *stringVal() {
  return token;
}

