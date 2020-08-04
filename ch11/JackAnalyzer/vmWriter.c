#include "sub.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void writePush(char *segment, int index){
  fprintf(vmOfp, "  push %s %d\n", segment, index);
}

void writePop(char *segment, int index){
  fprintf(vmOfp, "  pop %s %d\n", segment, index);
}

void writeArithmetic(char command){
  char cmd[32];
  if(command == '+') strcpy(cmd, "add");
  else if(command == '-') strcpy(cmd, "sub");
  else if(command == '*') strcpy(cmd, "Math.multiply");
  else if(command == '/') strcpy(cmd, "Math.divide");
  else if(command == '=') strcpy(cmd, "eq");
  else if(command == '&') strcpy(cmd, "and");
  else if(command == '|') strcpy(cmd, "or");
  else if(command == '<') strcpy(cmd, "lt");
  else if(command == '>') strcpy(cmd, "gt");
  else {
	printf("Unknown command in arithmetic\n");
	exit(1);
  }
	
  fprintf(vmOfp, "  %s\n", cmd);
}

void writeLabel(char *label){
  fprintf(vmOfp, "  label %s\n", label);
}

void writeGoto(char *label){
  fprintf(vmOfp, "  goto %s\n", label);
}

void writeIf(char *label){
  fprintf(vmOfp, "  if-goto %s\n", label);
}

void writeCall(char *name, int argc){
  fprintf(vmOfp, "  call %s %d\n", name, argc);
}

void writeFunction(char *name, int argc){
  fprintf(vmOfp, "function %s  %d\n", name, argc);
}

void writeReturn(){
  fprintf(vmOfp, "  return");
}

void close(){
  fclose(vmOfp);
}
