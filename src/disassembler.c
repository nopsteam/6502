#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sc_str.h"
#include "constants.h"
#include "disassembler.h"

struct OPCODE * GetOpcode(unsigned char hex) {
  int length = sizeof(opcodes) / sizeof(opcodes[0]);

  for(int i = 0; i < length; i++) {
    if (opcodes[i].hex == hex)
      return &opcodes[i];
  }

  return NULL;
}

struct PROGRAM LoadBinary(char * binaryPath) {
  if(strlen(binaryPath) <= 0) {
    printf("invalid file path %s", binaryPath);
    exit(1);
  }

  if(access(binaryPath, F_OK) != 0) {
    printf("file not found %s", binaryPath);
    exit(1);
  }

  FILE * file = fopen(binaryPath, "r");

  if(file == NULL) {
    printf("error opening file %s", binaryPath);
    exit(1);
  }

  // count file size
  fseek(file, 0, SEEK_END);
  int fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char buffer;
  int programLine = -1;
  int argumentCount = 0;
  struct OPCODE * opcode = NULL;
  struct PROGRAM_LINE * program = malloc(sizeof(* program) * fileSize);
  int offset = 0x600;

  while(fread(&buffer, 1, 1, file) > 0) {
    if (argumentCount > 0) {
      argumentCount--;
      program[programLine].args[argumentCount] = buffer;

      offset += 0x1;
      continue;
    }

    programLine++;

    opcode = GetOpcode(buffer);

    if(opcode == NULL) {
      printf("0x%02X => FAIL !!!", buffer & 0xFF);
      continue;
    }

    program[programLine].opcode = opcode;
    program[programLine].offset = offset;

    offset += 0x1;

    argumentCount = opcode->addressing->length - 1;
  }

  fclose(file);

  struct PROGRAM programLoaded = {
    .program = program,
    .lines = programLine + 1
  };

  return programLoaded;
}

char * toStringHex(struct PROGRAM_LINE * line) {
  char * string_line = sc_str_create("");
  unsigned char hex = line->opcode->hex;
  char firstOperand = line->args[0];
  char secondOperand = line->args[1];
  int byteSize = line->opcode->addressing->length - 1;

  switch(byteSize) {
    case 0:
      sc_str_append_fmt(&string_line, "%02x      ", hex & 0xFF);
      break;
    case 1:
      sc_str_append_fmt(&string_line, "%02x %02x   ", hex & 0xFF, firstOperand & 0xFF);
      break;
    case 2:
      sc_str_append_fmt(&string_line, "%02x %02x %02x", hex & 0xFF, secondOperand & 0xFF, firstOperand & 0xFF);
      break;
    default:
      sc_str_append_fmt(&string_line, "%s", "Invalid instruction");
  }

  return string_line;
}

char * toStringAsm(struct PROGRAM_LINE * line) {
  int nextAddress = line->offset + line->opcode->addressing->length;
  char * string_line = sc_str_create("");
  char * instruction = line->opcode->instruction->name;
  char firstOperand = line->args[0];
  char secondOperand = line->args[1];
  int addressMode = line->opcode->addressing->index;
  switch(addressMode) {
    case Implied:
      sc_str_append_fmt(&string_line, "%s ", instruction);
      break;
    case Accumulator:
      sc_str_append_fmt(&string_line, "%s A", instruction);
      break;
    case Immediate:
      sc_str_append_fmt(&string_line, "%s #$%02x", instruction, firstOperand & 0xFF);
      break;
    case ZeroPage:
      sc_str_append_fmt(&string_line, "%s $%02x", instruction, firstOperand & 0xFF);
      break;
    case ZeroPageX:
      sc_str_append_fmt(&string_line, "%s $%02x,X", instruction, firstOperand & 0xFF);
      break;
    case ZeroPageY:
      sc_str_append_fmt(&string_line, "%s $%02x,Y", instruction, firstOperand & 0xFF);
      break;
    case Relative:
      sc_str_append_fmt(&string_line, "%s $%04x", instruction, (nextAddress + firstOperand) & 0xFFFF);
      break;
    case IndirectX:
      sc_str_append_fmt(&string_line, "%s ($%02x,X)", instruction, firstOperand & 0xFF);
      break;
    case IndirectY:
      sc_str_append_fmt(&string_line, "%s ($%02x),Y", instruction, firstOperand & 0xFF);
      break;
    case AbsoluteX:
      sc_str_append_fmt(&string_line, "%s $%02x%02x,X", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
      break;
    case AbsoluteY:
      sc_str_append_fmt(&string_line, "%s $%02x%02x,Y", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
      break;
    case Absolute:
      sc_str_append_fmt(&string_line, "%s $%02x%02x", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
      break;
    case Indirect:
      sc_str_append_fmt(&string_line, "%s ($%02x%02x)", instruction, firstOperand & 0xFF, secondOperand & 0xFF);
      break;
    default:
      sc_str_append_fmt(&string_line, "%s", "Invalid address mode!");
  }

  return string_line;
}
