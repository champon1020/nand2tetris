#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "sub.h"

void initTokenizer();
bool hasMoreToken();
bool checkSymbol(char c);
bool checkKeyword(char *s);
int readNextCommand();
void advance();
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
bool isComment = false;
char buf[4096];

void modifyCommand(){
  int cur = 0, len = strlen(buf);
  while(cur < len && isspace(buf[cur])) ++cur;
  
  int pos = 0;
  while(cur < len && buf[cur] != '\n'){
	if(buf[cur] == '/' && buf[cur+1] == '*'){
	  isComment = true;
	  cur += 2;
	  continue;
	}
	if(buf[cur] == '*' && buf[cur+1] == '/'){
	  isComment = false;
	  memset(cmd, '\0', sizeof(cmd));
	  cur += 2;
	  continue;
	}
	if(buf[cur] == '/' && buf[cur+1] == '/'){
	  buf[cur] = '\0';
	  break;
	}
	cmd[pos++] = buf[cur++];
  }
}

int readNextCommand() {
  if(fgets(buf, sizeof(buf), fp) != NULL) {
	memset(cmd, '\0', sizeof(cmd));
	modifyCommand();
	if(isComment || cmd[0] == '\0')
	  readNextCommand();
	initTokenizer();
	return 1;
  }
  return 0;
}

void advance() {
  memset(token, '\0', sizeof(token));
  if(!hasMoreToken()){
	if(!readNextCommand()){
	  EOF_ = 1;
	  return;
	}
  }
  
  int pos = 0, len = strlen(cmd);
  while(commandCur < len){
	if(cmd[commandCur] == '"'){
	  isStr = !isStr;
	  token[pos++] = cmd[commandCur++];
	  if(!isStr) break;
	  continue;
	}
	if(!isStr){
	  if(isspace(cmd[commandCur])){
	    ++commandCur;
		break;
	  }
	  if(checkSymbol(cmd[commandCur])){
		if(!pos) token[0] = cmd[commandCur++]; 
		break;
	  }
	}
    token[pos++] = cmd[commandCur++];
  }

  if(!strcmp(tokenType(), "NULL")){
	advance();
  }
}

char *tokenType() {
  if(isspace(token[0]) || strlen(token) == 0)
	return "NULL";

  if(checkKeyword(token))
	return "KEYWORD";
  else if(token[0] == '"')
	return "STRING_CONST";
  else if(!isalnum(token[0]))
	return "SYMBOL";
  else if(checkIsNumber(token))
	return "INT_CONST";
  else
	return "IDENTIFIER";
}

char *keyWord() {
  char *kw = malloc(128 * sizeof(char *));
  int pos = 0, cur = 0, len = strlen(token);
  while(cur < len) {
    kw[pos++] = toupper(token[cur++]);
  }
  return kw;
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
  char *strVal = malloc(strlen(token) * sizeof(char *));
  int cur = 1, pos = 0, len = strlen(token);
  while(cur < len-1) {
    strVal[pos++] = token[cur++];
  }
  return strVal;
}

