#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sub.h"

void pushCmd(char *seg, int index);
void popCmd(char *seg, int index);
char *getSymbol(char *seg);
void calcOp(char *cmd);
void incrementAddress(int index);
void pushOnStack();
void popOnStack();

void writeArthmetic(char *cmd){
  if(!strcmp(cmd, "lt") ||
	 !strcmp(cmd, "gt") ||
	 !strcmp(cmd, "eq")){
	calcOp(cmd);
	return;
  }
  
  // pop lhs
  popOnStack();
  if(!strcmp(cmd, "neg")){
	fprintf(ofp, "D=-M\n");
	pushOnStack();
	return;
  }
  if(!strcmp(cmd, "not")){
	fprintf(ofp, "D=!M\n");
	pushOnStack();
	return;
  }
  
  // pop rhs
  fprintf(ofp, "D=M\n");
  popOnStack();
  if(!strcmp(cmd, "add")){
	fprintf(ofp, "D=M+D\n");
	pushOnStack();
  }
  if(!strcmp(cmd, "sub")){
	fprintf(ofp, "D=M-D\n");
	pushOnStack();
  }
  if(!strcmp(cmd, "or")){
	fprintf(ofp, "D=M|D\n");
	pushOnStack();
  }
  if(!strcmp(cmd, "and")){
	fprintf(ofp, "D=M&D\n");
	pushOnStack();
  }
}

void writePushPop(char *cmd, char *seg, int index){
  if(!strcmp(cmd, "push")) pushCmd(seg, index);
  if(!strcmp(cmd, "pop")) popCmd(seg, index);
}

void pushCmd(char *seg, int index){
  if(!strcmp(seg, "constant")){
	fprintf(ofp, "@%d\nD=A\n", index);
	pushOnStack();
	return;
  }

  if(!strcmp(seg, "static")){
	fprintf(ofp, "@%s.%d\nD=M\n", currentBaseName, index);
	pushOnStack();
	return;
  }
  
  if(!strcmp(seg, "temp")){
	fprintf(ofp, "@%d\n", 5);
  }else if(!strcmp(seg, "pointer")){
    fprintf(ofp, "@%d\n", 3);
  }else{
    fprintf(ofp, "@%s\n", getSymbol(seg));
	fprintf(ofp, "A=M\n");
  }
  incrementAddress(index);
  fprintf(ofp, "D=M\n");
  pushOnStack();
}

void popCmd(char *seg, int index){
  popOnStack();
  fprintf(ofp, "D=M\n");

  if(!strcmp(seg, "static")){
	fprintf(ofp, "@%s.%d\nM=D\n", currentBaseName, index);
	return;
  }
  
  if(!strcmp(seg, "temp")){
	fprintf(ofp, "@%d\n", 5);
  }else if(!strcmp(seg, "pointer")){
    fprintf(ofp, "@%d\n", 3);
  }else{
    fprintf(ofp, "@%s\n", getSymbol(seg));
	fprintf(ofp, "A=M\n");
  }
  incrementAddress(index);
  fprintf(ofp, "M=D\n");
}

char *getSymbol(char *seg){
  if(!strcmp(seg, "local"))
	return "LCL";
  if(!strcmp(seg, "argument"))
	return "ARG";
  if(!strcmp(seg, "this"))
	return "THIS";
  if(!strcmp(seg, "that"))
	return "THAT";

  printf("Symbol is not valid: %s\n", seg);
  exit(1);
}

void incrementAddress(int index){
  for(int i=0; i<index; i++){
	fprintf(ofp, "A=A+1\n");
  }
}

void calcOp(char *op){
  char *jump = malloc(32);
  if(!strcmp(op, "eq")){
    jump = "JEQ";
  }
  if(!strcmp(op, "gt")){
    jump = "JGT";
  }
  if(!strcmp(op, "lt")){
    jump = "JLT";
  }

  int l1 = labelCnt++;
  int l2 = labelCnt++;

  popOnStack();
  fprintf(ofp, "D=M\n");
  popOnStack();
  fprintf(ofp, "D=M-D\n");
  fprintf(ofp, "@L%d\n", l1);
  fprintf(ofp, "D;%s\n", jump);
  fprintf(ofp, "D=0\n");
  fprintf(ofp, "@L%d\n0;JMP\n", l2);
  fprintf(ofp, "(L%d)\nD=-1\n", l1);
  fprintf(ofp, "(L%d)\n", l2);
  pushOnStack();
}

void pushOnStack(){
  fprintf(ofp, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
}

void popOnStack(){
  fprintf(ofp, "@SP\nM=M-1\nA=M\n");
}
