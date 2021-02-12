#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
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

  for (int i = 0; i < programLoaded.lines; i++) {
    char * instruction = programLoaded.program[i].opcode->instruction;
    char firstOperand = programLoaded.program[i].args[0];
    char secondOperand = programLoaded.program[i].args[1];
    int addressMode = programLoaded.program[i].opcode->addressing->index;

    switch(addressMode) {
      case Implied:
        printf("%s\n", instruction);
        break;
      case Accumulator:
        printf("%s A\n", instruction);
        break;
      case Immediate:
        printf("%s #$%02x \n", instruction, firstOperand & 0xFF);
        break;
      case ZeroPage:
        printf("%s $%02x \n", instruction, firstOperand & 0xFF);
        break;
      case ZeroPageX:
        printf("%s $%02x,X \n", instruction, firstOperand & 0xFF);
        break;
      case ZeroPageY:
        printf("%s $%02x,Y \n", instruction, firstOperand & 0xFF);
        break;
      case Relative:
        printf("%s 0x%02x \n", instruction, firstOperand & 0xFF);
        break;
      case IndirectX:
        printf("%s ($%02x,X) \n", instruction, firstOperand & 0xFF);
        break;
      case IndirectY:
        printf("%s ($%02x),Y \n", instruction, firstOperand & 0xFF);
        break;
      case AbsoluteX:
        printf("%s $%02x%02x,X \n", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
        break;
      case AbsoluteY:
        printf("%s $%02x%02x,Y \n", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
        break;
      case Absolute:
        printf("%s $%02x%02x \n", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
        break;
      case Indirect:
        printf("%s ($%02x%02x) \n", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
        break;
      default:
        printf("more than 2 operands is not supported");
    }
  }

  free(programLoaded.program);
  return 0; 
}
