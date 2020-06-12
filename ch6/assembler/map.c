#include <string.h>
#include <stdlib.h>

typedef struct _node {
  char *key;
  struct _node *par, *left, *right;
} Node;

Node *root, *NIL;

void insert(char *k) {
  Node *cur = root;
  Node *pre = NIL;
  Node *x = malloc(sizeof(Node));

  x->key = k;
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
  while(cur != NIL && k != cur->key){
	if(strcmp(k, cur->key) < 0)
	  cur = cur->left;
	else
	  cur = cur->right;
  }
  return cur;
}
