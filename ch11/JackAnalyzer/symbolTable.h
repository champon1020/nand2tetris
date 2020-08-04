#ifndef _INCLUDE_SYMBOL_TABLE_H_
#define _INCLUDE_SYMBOL_TABLE_H_

void initSymbolTable();
void startSubroutine();
void define(char *name, char *type, Kind kind);
int varCount(char *kind);
Kind kindOf(char *name);
char *typeOf(char *name);
int indexOf(char *name);

#endif //_INCLUDE_SYMBOL_TABLE_H_
