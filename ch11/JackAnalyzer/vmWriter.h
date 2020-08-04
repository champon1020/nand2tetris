#ifndef _INCLUDE_VM_WRITER_H_
#define _INCLUDE_VM_WRITER_H_

void writePush(char *segment, int index);
void writePop(char *segment, int index);
void writeArithmetic(char command);
void writeLabel(char *label);
void writeGoto(char *label);
void writeIf(char *label);
void writeCall(char *name, int argc);
void writeFunction(char *name, int argc);
void writeReturn();
void close();

#endif //_INCLUDE_VM_WRITER_H_
