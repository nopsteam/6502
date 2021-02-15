#include "program.h"

struct OPCODE * GetOpcode(char hex);
struct PROGRAM LoadBinary(char * binaryPath);
char* toStringHex(struct PROGRAM_LINE * line);
char* toStringAsm(struct PROGRAM_LINE * line);
