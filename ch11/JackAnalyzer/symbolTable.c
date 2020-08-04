#include <stdlib.h>
#include <string.h>
#include "sub.h"


Table findByName(char *name);

Table staticTable[4096];
Table fieldTable[4096];
Table argTable[4096];
Table varTable[4096];
int staticCur = 0, fieldCur = 0, argCur = 0, varCur = 0;

void initSymbolTable(){
  memset(&staticTable, 0, sizeof(staticTable));
  memset(&fieldTable, 0, sizeof(fieldTable));
  memset(&argTable, 0, sizeof(argTable));
  memset(&varTable, 0, sizeof(varTable));
}

void startSubroutine(){
  initSymbolTable();
}

void define(char *name, char *type, Kind kind){
  Table t;
  t.name = malloc(sizeof(char *) * 128);
  t.type = malloc(sizeof(char *) * 128);
  strcpy(t.name, name);
  strcpy(t.type, type);
  t.kind = kind;
  
  if(t.kind == STATIC) staticTable[staticCur++] = t;
  else if(t.kind == FIELD) fieldTable[fieldCur++] = t;
  else if(t.kind == ARG) argTable[argCur++] = t;
  else if(t.kind == VAR) varTable[varCur++] = t;
  else{
	printf("Unknown kind\n");
	exit(1);
  }
}

int varCount(Kind kind){
  if(kind == STATIC) return staticCur;
  else if(kind == FIELD) return fieldCur;
  else if(kind == ARG) return argCur;
  else if(kind == VAR) return varCur;
  return 0;
}

Kind kindOf(char *name){
  Table t = findByName(name);
  return t.kind;
}

char *typeOf(char *name){
  Table t = findByName(name);
  return t.type;
}

int indexOf(char *name){
  Table t = findByName(name);
  return varCount(t.kind);
}

Table findByName(char *name){
  // search static table
  for(int i=0; i<staticCur; i++){
	if(!strcmp(name, staticTable[i].name))
	  return staticTable[i];
  }

  // search field table
  for(int i=0; i<fieldCur; i++){
	if(!strcmp(name, fieldTable[i].name))
	  return fieldTable[i];
  }

  // search arg table
  for(int i=0; i<argCur; i++){
	if(!strcmp(name, argTable[i].name))
	  return argTable[i];
  }

  // search var table
  for(int i=0; i<varCur; i++){
	if(!strcmp(name, varTable[i].name))
	  return varTable[i];
  }

  Table dummy = {"-1", "none", NONE};
  return dummy;
}
