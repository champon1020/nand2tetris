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
	}
	if(!strcmp(keyWord(), "CONSTRUCTOR") ||
	   !strcmp(keyWord(), "FUNCTION") ||
	   !strcmp(keyWord(), "METHOD")){
	  compileSubroutine();
	}
	break;
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
  writeTerminal("identifier", token, layer);
  advance();

  // name
  bool flg = false;
  while(!strcmp(tokenType(), "IDENTIFIER") ||
		(!strcmp(tokenType(), "SYMBOL") && symbol() == ',')){
	if(flg){
	  writeTerminal("symbol", token, layer);
	  advance();
	}
    flg = true;
	writeTerminal("identifier", token, layer);
	advance();
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
  advance();

  // type
  writeTerminal("identifier", token, layer);
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
  writeStartTag("subroutineBody", layer++);
  // {
  writeTerminal("symbol", token, layer);
  advance();
  
  while(!strcmp(tokenType(), "KEYWORD")){
	if(!strcmp(keyWord(), "VAR")){
	  compileVarDec();
	}
	if(!strcmp(keyWord(), "LET")){
	  compileStatements();
	  break;
	}
  }

  // }
  writeTerminal("symbol", token, layer);
  advance();
  writeEndTag("subroutineBody", --layer);
  
  writeEndTag("subroutineDec", --layer);
}

void compileParameterList() {
  bool flg = false;
  while(!strcmp(tokenType(), "IDENTIFIER") ||
		(!strcmp(tokenType(), "SYMBOL") && symbol() == ',')){
	if(!flg) {
	  writeStartTag("parameterList", layer++);
	}else{
	  writeTerminal("symbol", token, layer);
	  advance();
	}
    flg = true;
	writeTerminal("identifier", token, layer);
	advance();
  }

  if(flg)
	writeEndTag("parameterList", --layer);
}

void compileVarDec() {
  writeStartTag("varDec", layer++);

  // var
  writeTerminal("keyword", token, layer);
  advance();

  // type
  writeTerminal("identifier", token, layer);
  advance();

  bool flg = false;
  while(!strcmp(tokenType(), "IDENTIFIER") ||
		(!strcmp(tokenType(), "SYMBOL") && symbol() == ',')){
	if(flg) {
	  writeTerminal("symbol", token, layer);
	  advance();
	}
	flg = true;
	writeTerminal("identifier", token, layer);
	advance();
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
	}
	if(!strcmp(keyWord(), "IF")){
	  compileIf();
	}
	if(!strcmp(keyWord(), "DO")){
	  compileDo();
	}
	if(!strcmp(keyWord(), "WHILE")){
	  compileWhile();
	}
	if(!strcmp(keyWord(), "RETURN")){
	  compileReturn();
	}
  }

  writeEndTag("statements", --layer);
}

void compileExpression() {
  writeStartTag("expression", layer++);

  

  writeEndTag("expression", --layer);
}

void compileTerm() {
}

void compileExpressionList(){
}

void compileLet() {
  writeStartTag("letStatement", layer++);

  // let
  writeTerminal("keyword", token, layer);
  advance();

  // name
  writeTerminal("identifier", token, layer);
  advance();

  // [exp]
  if(!strcmp(tokenType(), "SYMBOL") && symbol() == '['){
	// [
	writeTerminal("symbol", token, layer);

	compileExpression();

	// ]
	writeTerminal("symbol", token, layer);
  }

  // =
  writeTerminal("symbol", token, layer);
  advance();

  compileExpression();

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

  if(!strcmp(tokenType(), "KEYWORD") && !strcmp(keyword(), "else")) {
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

  compileSubroutine();

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

  compileExpression();

  // ;
  writeTerminal("symbol", token, layer);
  advance();

  writeEndTag("returnStatement", --layer);
}
