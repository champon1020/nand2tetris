#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char *fill(char *s, int size){
  char *res = malloc(sizeof(char)*size);
  int cur = 0;
  while(cur + strlen(s) < size)
	res[cur++] = '0';

  int i = 0;
  while(i < strlen(s))
	res[cur++] = s[i++];

  return res;
}

char *reverse(char *s) {
  char *res = malloc(sizeof(s));
  int cur = 0;
  while(cur < strlen(s)){
	res[cur] = s[strlen(s)-cur-1];
	cur++;
  }
  return res;
}

char *convertBin(char *symbol) {
  int cur = 0;
  int judge = 1;
  while(cur < strlen(symbol)){
	if(!isdigit(symbol[cur++]))
	  judge = 0;
  }

  if(!judge)
	return NULL;

  cur = 0;
  int n = atoi(symbol);
  char *buf = malloc(128);
  while(n > 0){
	buf[cur++] = (char)(n%2 + '0');
	n = n/2;
  }

  char *res = fill(reverse(buf), 16);
  return res;
}

