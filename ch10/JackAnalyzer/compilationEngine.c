#include <string.h>
#include <stdlib.h>
#include "sub.h"
#include "tokenizer.h"

void compileClass();
void compileClassVarDec();
void compileSubroutine();
void compileParameterList();
void compileVarDec();
void compileStatements();
void compileDo();
void compileLet();
void compileWhile();
void compileReturn();
void compileIf();
void compileExpression();
void compileTerm();
void compileExpressionList();

void compileSubroutineCall();


int layer = 0;

char *indentStr(int indent) {
  char *idt = malloc(2*indent*sizeof(char *));
  memset(idt, ' ', 2*indent);
  return idt;
}

void writeStartTag(char *tagName, int indent) {
  fprintf(ofp, "%s<%s>\n", indentStr(indent), tagName);
}

void writeEndTag(char *tagName, int indent) {
  fprintf(ofp, "%s</%s>\n", indentStr(indent), tagName);
}

void writeTerminal(char *tagName, char *terminal, int indent) {
  fprintf(ofp, "%s<%s> %s </%s>\n", indentStr(indent), tagName, terminal, tagName);
}

void compileClass() {
  writeStartTag("class", layer++);

  // class keyword
  writeTerminal("keyword", "class", layer);
  advance();

  // class name
  writeTerminal("identifier", token, layer);
  advance();

  // {
  writeTerminal("symbol", token, layer);
  advance();
  
  while(!strcmp(tokenType(), "KEYWORD")){
	if(!strcmp(keyWord(), "STATIC") ||
	   !strcmp(keyWord(), "FIELD")){
	  compileClassVarDec();
	}else if(!strcmp(keyWord(), "CONSTRUCTOR") ||
	   !strcmp(keyWord(), "FUNCTION") ||
	   !strcmp(keyWord(), "METHOD")){
	  compileSubroutine();
	}else{
	  break;
	}
  }

  // }
  writeTerminal("symbol", token, layer);
  
  writeEndTag("class", --layer);
}

void compileClassVarDec() {
  writeStartTag("classVarDec", layer++);

  // keyword
  writeTerminal("keyword", token, layer);
  advance();

  // type
  if(checkKeyword(token))
	writeTerminal("keyword", token, layer);
  else
	writeTerminal("identifier", token, layer);
  advance();

  // name
  while(!strcmp(tokenType(), "IDENTIFIER")){
	writeTerminal("identifier", token, layer);
	advance();
	
	if(!strcmp(tokenType(), "SYMBOL") && symbol() == ','){
	  writeTerminal("symbol", token, layer);
	  advance();
	}
  }

  // ;
  writeTerminal("symbol", token, layer);
  advance();

  writeEndTag("classVarDec", --layer);
}

void compileSubroutine() {
  writeStartTag("subroutineDec", layer++);

  // keyword
  writeTerminal("keyword", token, layer);
  int isConstructor = !strcmp(token, "constructor");
  advance();

  // type or constructor name
  if(isConstructor)
	writeTerminal("identifier", token, layer);
  else
	writeTerminal("keyword", token, layer);
  advance();

  // name
  writeTerminal("identifier", token, layer);
  advance();

  // (
  writeTerminal("symbol", token, layer);
  advance();

  compileParameterList();

  // )
  writeTerminal("symbol", token, layer);
  advance();

  // subroutineBody
  {
	writeStartTag("subroutineBody", layer++);
	
	// {
	writeTerminal("symbol", token, layer);
	advance();
	
	while(!strcmp(tokenType(), "KEYWORD")){
	  if(!strcmp(keyWord(), "VAR")){
		compileVarDec();
	  }else{
		compileStatements();
	  }
	}

	// }
	writeTerminal("symbol", token, layer);
	advance();
	
	writeEndTag("subroutineBody", --layer);
  }
  
  writeEndTag("subroutineDec", --layer);
}

void compileParameterList() {
  writeStartTag("parameterList", layer++);

  while(!strcmp(tokenType(), "KEYWORD")){
	// type
	writeTerminal("keyword", token, layer);
	advance();
	
	// varName
	writeTerminal("identifier", token, layer);
	advance();

	if(!strcmp(tokenType(), "SYMBOL") && symbol() == ','){
	  // ,
	  writeTerminal("symbol", token, layer);
	  advance();
	}
  }

  writeEndTag("parameterList", --layer);
}

void compileVarDec() {
  writeStartTag("varDec", layer++);

  // var
  writeTerminal("keyword", token, layer);
  advance();

  // type
  if(checkKeyword(token))
	writeTerminal("keyword", token, layer);
  else
	writeTerminal("identifier", token, layer);
  advance();

  while(!strcmp(tokenType(), "IDENTIFIER")){
	// varName
	writeTerminal("identifier", token, layer);
	advance();

	// ,
	if(!strcmp(tokenType(), "SYMBOL") && symbol() == ','){
	  writeTerminal("symbol", token, layer);
	  advance();
	}
  }

  // ;
  writeTerminal("symbol", token, layer);
  advance();
  
  writeEndTag("varDec", --layer);
}

void compileStatements() {
  writeStartTag("statements", layer++);

  while(!strcmp(tokenType(), "KEYWORD")){
	if(!strcmp(keyWord(), "LET")){
	  compileLet();
	}else if(!strcmp(keyWord(), "IF")){
	  compileIf();
	}else if(!strcmp(keyWord(), "DO")){
	  compileDo();
	}else if(!strcmp(keyWord(), "WHILE")){
	  compileWhile();
	}else if(!strcmp(keyWord(), "RETURN")){
	  compileReturn();
	}else{
	  printf("%s\n", token);
	  exit(1);
	  break;
	}
  }

  writeEndTag("statements", --layer);
}

void compileExpression() {
  writeStartTag("expression", layer++);

  compileTerm();

  if(!strcmp(tokenType(), "SYMBOL")){
	// + - * / etc...
	if(symbol() == '+' ||
	   symbol() == '-' ||
	   symbol() == '*' ||
	   symbol() == '/' ||
	   symbol() == '&' ||
	   symbol() == '|' ||
	   symbol() == '<' ||
	   symbol() == '>' ||
	   symbol() == '='){
	  
	  writeTerminal("symbol", convertSymbol(token), layer);
	  advance();
	  
	  compileTerm();
	}
  }

  writeEndTag("expression", --layer);
}

void compileTerm() {
  writeStartTag("term", layer++);

  if(!strcmp(tokenType(), "INT_CONST")){
	/*
	  integerConst
	*/
	writeTerminal("integerConstant", token, layer);
	advance();
  }else if(!strcmp(tokenType(), "STRING_CONST")){
	/* 
	   stringConst
	*/
	writeTerminal("stringConstant", stringVal(), layer);
	advance();
  }else if(!strcmp(tokenType(), "IDENTIFIER")){
	char *identifier = malloc(sizeof(strlen(token)));
	strcpy(identifier, token);
	advance();

	if(!strcmp(tokenType(), "SYMBOL")){
	  if(symbol() == '['){
		/*
		  varName [ expression ]
		*/

		// varName
		writeTerminal("identifier", identifier, layer);
	  
		// [
		writeTerminal("symbol", token, layer);
		advance();

		compileExpression();

		//[
		writeTerminal("symbol", token, layer);
		advance();
	  }else if(symbol() == '(' || symbol() == '.'){
		/*
		  subroutineName ( expressionList )
		  or
		  (className | varName) . subroutineName ( expressionList)
		*/
		compileSubroutineCall(identifier);
	  }else{
		writeTerminal("identifier", identifier, layer);
	  }
	}else{
	  // varName
	  writeTerminal("identifier", identifier, layer);
	}
  }else if(!strcmp(tokenType(), "SYMBOL")){
	if(symbol() == '('){
	  /* 
		 ( expression )
	  */
	  
	  // (
	  writeTerminal("symbol", token, layer);
	  advance();

	  compileExpression();

	  // )
	  writeTerminal("symbol", token, layer);
	  advance();
	}else{
	  /*
		unaryOp term
	  */
	  
	  // - or ~
	  writeTerminal("symbol", token, layer);
	  advance();

	  compileTerm();
	}
  }else if(!strcmp(tokenType(), "KEYWORD")){
	writeTerminal("keyword", token, layer);
	advance();
  }else{
	printf("ERROR: infinite loop\n");
	printf("%s %s\n", tokenType(), token);
	exit(1);
  }

  writeEndTag("term", --layer);
}

void compileSubroutineCall(char *firstIdentifier) {
  writeTerminal("identifier", firstIdentifier, layer);

  if(symbol() == '.'){
	// .
	writeTerminal("symbol", token, layer);
	advance();

	// subroutineName
	writeTerminal("identifier", token, layer);
	advance();
  }
  
  // (
  writeTerminal("symbol", token, layer);
  advance();
  
  compileExpressionList();
	
  // )
  writeTerminal("symbol", token, layer);
  advance();
}

void compileExpressionList(){
  writeStartTag("expressionList", layer++);
  
  while(!(!strcmp(tokenType(), "SYMBOL") && symbol() == ')')){
	compileExpression();

	// ,
	if(!strcmp(tokenType(), "SYMBOL") && symbol() == ','){
	  writeTerminal("symbol", token, layer);
	  advance();
	}
  }

  writeEndTag("expressionList", --layer);
}

void compileLet() {
  writeStartTag("letStatement", layer++);

  // let
  writeTerminal("keyword", token, layer);
  advance();

  // name
  writeTerminal("identifier", token, layer);
  advance();

  /*
	[ expression ]
  */
  if(!strcmp(tokenType(), "SYMBOL") && symbol() == '['){
	// [
	writeTerminal("symbol", token, layer);
	advance();

	compileExpression();

	// ]
	writeTerminal("symbol", token, layer);
	advance();
  }

  // =
  writeTerminal("symbol", token, layer);
  advance();

  compileExpression();

  // ;
  writeTerminal("symbol", token, layer);
  advance();

  writeEndTag("letStatement", --layer);
}

void compileIf() {
  writeStartTag("ifStatement", layer++);

  // if
  writeTerminal("keyword", token, layer);
  advance();

  // (
  writeTerminal("symbol", token, layer);
  advance();

  compileExpression();

  // )
  writeTerminal("symbol", token, layer);
  advance();

  // {
  writeTerminal("symbol", token, layer);
  advance();

  compileStatements();

  // }
  writeTerminal("symbol", token, layer);
  advance();

  if(!strcmp(tokenType(), "KEYWORD") && !strcmp(token, "else")) {
	// else
	writeTerminal("keyword", token, layer);
	advance();

	// {
	writeTerminal("symbol", token, layer);
	advance();

	compileStatements();

	// }
	writeTerminal("symbol", token, layer);
	advance();
  }
  
  writeEndTag("ifStatement", --layer);
}

void compileDo() {
  writeStartTag("doStatement", layer++);

  // do
  writeTerminal("keyword", token, layer);
  advance();

  char *identifier = malloc(sizeof(strlen(token)));
  strcpy(identifier, token);
  advance();
  
  compileSubroutineCall(identifier);

  // ;
  writeTerminal("symbol", token, layer);
  advance();

  writeEndTag("doStatement", --layer);
}

void compileWhile() {
  writeStartTag("whileStatement", layer++);

  // while
  writeTerminal("keyword", token, layer);
  advance();

  // (
  writeTerminal("symbol", token, layer);
  advance();

  compileExpression();

  // )
  writeTerminal("symbol", token, layer);
  advance();

  // {
  writeTerminal("symbol", token, layer);
  advance();

  compileStatements();

  // }
  writeTerminal("symbol", token, layer);
  advance();

  writeEndTag("whileStatement", --layer);
}

void compileReturn() {
  writeStartTag("returnStatement", layer++);

  // return
  writeTerminal("keyword", token, layer);
  advance();

  if(strcmp(tokenType(), "SYMBOL")){
	compileExpression();
  }

  // ;
  writeTerminal("symbol", token, layer);
  advance();

  writeEndTag("returnStatement", --layer);
}
