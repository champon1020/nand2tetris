#include <stdlib.h>
#include <string.h>
#include "sub.h"
#include "vmWriter.h"
#include "symbolTable.h"


void compileVar(char *name, char *type, Kind kind){
  if(kindOf(name) == NONE){
	define(name, type, kind);
  }
  
  if(kind == STATIC) writePush("static", indexOf(name));
  else if(kind == FIELD) writePush("field", indexOf(name));
  else if(kind == ARG) writePush("argument", indexOf(name));
  else if(kind == VAR) writePush("local", indexOf(name));

  printf("name: %-10s type: %-10s kind: %-10d\n", name, type, kind);
}
