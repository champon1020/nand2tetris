#ifndef _INCLUDE_SUB_H_
#define _INCLUDE_SUB_H_

#include <stdio.h>

FILE *fp;
FILE *xmlOfp;
FILE *vmOfp;
int EOF_;
char cmd[4096];
char token[2048];

typedef enum K { STATIC, FIELD, ARG, VAR, NONE } Kind;

typedef struct table {
  char *name;
  char *type;
  Kind kind;
} Table;

#endif //_INCLUDE_SUB_H_
