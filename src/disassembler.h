#include "program.h"

struct OPCODE * GetOpcode(unsigned char hex);
int LoadBinary(char * binaryPath, struct PROGRAM * programLoaded);
char* toStringHex(struct PROGRAM_LINE * line);
char* toStringAsm(struct PROGRAM_LINE * line);
