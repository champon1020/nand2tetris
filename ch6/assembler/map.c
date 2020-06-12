#include <string.h>
#include <stdlib.h>
#include "sub.h"

void insert(char *k, char *v) {
  Node *cur = root;
  Node *pre = NIL;
  Node *x = malloc(sizeof(Node));

  x->key = k;
  x->val = v;
  x->left = NIL;
  x->right = NIL;

  while(cur != NIL){
	pre = cur;
	if(strcmp(x->key, cur->key) < 0)
	  cur = cur->left;
	else
	  cur = cur->right;
  }

  x->par = pre;

  if(pre == NIL)
	root = x;
  else{
	if(strcmp(x->key, pre->key) < 0)
	  pre->left = x;
	else
	  pre->right = x;
  }
}

Node *find(char *k){
  Node *cur = root;
  while(cur != NIL && strcmp(k, cur->key)){
	if(strcmp(k, cur->key) < 0)
	  cur = cur->left;
	else
	  cur = cur->right;
  }
  return cur;
}
