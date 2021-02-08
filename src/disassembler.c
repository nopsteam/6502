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

void LoadBinary(char * binaryPath) {
  //forneceu algum conteúdo como argumento?
  if(strlen(binaryPath) <= 0)
    return;

  //o arquivo existe no disco? 
  if(access(binaryPath, F_OK) != 0) {
    printf("arquivo não encontrado %s", binaryPath);
    return;
  }

  //abre arquivo em modo de leitura
  FILE * file = fopen(binaryPath, "r");

  //se não conseguiu um identificador, deu problema ao abrir o arquivo
  if(file == NULL) {
    printf("erro ao abrir arquivo %s", binaryPath);
    return;
  }

  //lendo um arquivo byte a byte
  char buffer;
  int jumps = 0;
  while(fread(&buffer, 1, 1, file) > 0) {
    //por enquanto, ignorando os argumentos para entender se os opcodes são identificados corretamente
    if (jumps > 0) {
      jumps--;
      continue;
    }

    //identifica opcode baseado no byte lido do arquivo
    struct OPCODE * opcode = GetOpcode(buffer);

    if(opcode == NULL) {
      printf("0x%02X => FAIL !!!\n", buffer & 0xFF);
      continue;
    }
    else 
      printf("0x%02X = %s\n", buffer & 0xFF, opcode->instruction);

    //adiciona argumentos para ignorar nas próximas iterações, jumps-- no começo do while
    jumps = opcode->addressing->length - 1;
  }

  //fechando o arquivo para não ter memory leak
  fclose(file);
}
