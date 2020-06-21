#ifndef _INCLUDE_CODE_WRITER_H_
#define _INCLUDE_CODE_WRITER_H_

void writeInit();
void writeLabel(char *label);
void writeGoto(char *label);
void writeIf(char *label);
void writeCall(char *funcName, int argc);
void writeReturn();
void writeFunction(char *funcName, int argc);
void writeArthmetic(char *cmd);
void writePushPop(char *cmd, char *seg, int index);

#endif //_INCLUDE_CODE_WRITER_H_
