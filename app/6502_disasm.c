#include <stdio.h>
#include <stdlib.h>
#include "disassembler.h"

int main(int argc, char **argv)
{
  char * programPath = NULL;
  if (argc > 1) {
    programPath = argv[1];
  } else {
    programPath = "resources/dump.bin";
  }
  struct PROGRAM programLoaded = LoadBinary(programPath);

  printf("Address  Hexdump   Dissassembly\n");
  printf("-------------------------------\n");

  for (int i = 0; i < programLoaded.lines; i++) {
    printf("$%04x    ", programLoaded.program[i].offset);
    printf("%s  ", toStringHex(&programLoaded.program[i]));
    printf("%s\n", toStringAsm(&programLoaded.program[i]));
  }

  free(programLoaded.program);
  return 0;
}
