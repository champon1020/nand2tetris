#ifndef _INCLUDE_TOKENIZER_H_
#define _INCLUDE_TOKENIZER_H_

#include <stdbool.h>

void initTokenizer();
bool hasMoreToken();
bool checkKeyword();
void advance();
char *tokenType();
char *keyWord();
char symbol();
char *identifier();
int inVal();
char *stringVal();

#endif //_INCLUDE_TOKENIZER_H_
