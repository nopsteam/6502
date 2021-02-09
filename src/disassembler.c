#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"

struct OPCODE * GetOpcode(char hex) {
  int length = sizeof(opcodes) / sizeof(opcodes[0]);

  for(int i = 0; i < length; i++) {
    if (opcodes[i].hex == hex)
      return &opcodes[i];
  }

  return NULL;
}

struct PROGRAM LoadBinary(char * binaryPath) {
  //forneceu algum conteúdo como argumento?
  if(strlen(binaryPath) <= 0) {
    printf("invalid file path %s", binaryPath);
    exit(0);
  }

  //o arquivo existe no disco? 
  if(access(binaryPath, F_OK) != 0) {
    printf("arquivo não encontrado %s", binaryPath);
    exit(0);
  }

  //abre arquivo em modo de leitura
  FILE * file = fopen(binaryPath, "r");

  //se não conseguiu um identificador, deu problema ao abrir o arquivo
  if(file == NULL) {
    printf("erro ao abrir arquivo %s", binaryPath);
    exit(0);
  }

  // seek to end of file
  fseek(file, 0, SEEK_END);
  // get current file pointer
  int fileSize = ftell(file);
  // seek back to beginning of file
  fseek(file, 0, SEEK_SET);

  //lendo um arquivo byte a byte
  char buffer;
  int programLine = -1;
  int argumentCount = 0;
  struct OPCODE * opcode = NULL;

  struct PROGRAM_LINE * program = malloc(sizeof(* program) * fileSize);

  while(fread(&buffer, 1, 1, file) > 0) {
    //por enquanto, ignorando os argumentos para entender se os opcodes são identificados corretamente
    if (argumentCount > 0) {
      argumentCount--;
      program[programLine].args[argumentCount] = buffer;
      continue;
    }

    programLine++;

    //identifica opcode baseado no byte lido do arquivo
    opcode = GetOpcode(buffer);

    if(opcode == NULL) {
      printf("0x%02X => FAIL !!!\n", buffer & 0xFF);
      continue;
    }

    program[programLine].opcode = opcode;

    //adiciona argumentos para ignorar nas próximas iterações, argumentCount-- no começo do while
    argumentCount = opcode->addressing->length - 1;
  }

  //fechando o arquivo para não ter memory leak
  fclose(file);

  struct PROGRAM programLoaded = {
    .program = program,
    .lines = programLine + 1 // +1 por conta da variável iniciar em -1, ou seja, conta a linha 0;
  };

  return programLoaded ;
}
