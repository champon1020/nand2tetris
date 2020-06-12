#ifndef _INCLUDE_SUB_H_
#define _INCLUDE_SUB_H_

typedef struct _node {
  char *key, *val;
  struct _node *par, *left, *right;
} Node;

char buf[4096];
char cmd[4096];
Node *root, *NIL;

#endif //_INCLUDE_SUB_H_
