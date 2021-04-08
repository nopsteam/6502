#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "bus.h"

struct BUS initializeBus() {
  struct BUS bus;

  bus.input = 0x00;

  for(int i = 0; i < 1024; ++i)
  {
    bus.display[i] = 0x00;
  }

  for(int i = 0; i < (64 * 1024); ++i)
  {
    bus.memory[i] = 0x00;
  }

  return bus;
}

void writeBus(unsigned int addr, unsigned char data, struct BUS * bus) {
  if ((addr >= 0x0000 && addr <  0x00FF) ||
      (addr >  0x00FF && addr <  0x0200) ||
      (addr >  0x05FF && addr <= 0xFFFF))
  {
    bus->memory[addr] = data;
  }
  else if (addr >= 0x0200 && addr <= 0x05FF)
  {
    bus->display[addr - 0x0200] = data;
  }
  else if (addr == 0x00FF)
  {
    bus->input = data;
  }
  return;
}

unsigned char readBus(unsigned int addr, struct BUS * bus) {
  unsigned char data = 0x00;

  if ((addr >= 0x0000 && addr <  0x00FF) ||
      (addr >  0x00FF && addr <  0x0200) ||
      (addr >  0x05FF && addr <= 0xFFFF))
  {
    data = bus->memory[addr];
  }
  else if (addr >= 0x0200 && addr <= 0x05FF)
  {
    data = bus->display[addr - 0x0200];
  }
  else if (addr == 0x00FF)
  {
    data = bus->input;
  }

  return data;
}

void writeProgramToBus(char * filePath, unsigned int offset, struct BUS * bus) {
  if(strlen(filePath) <= 0) {
    printf("invalid file path %s", filePath);
    exit(1);
  }

  if(access(filePath, F_OK) != 0) {
    printf("file not found %s", filePath);
    exit(1);
  }

  FILE * file = fopen(filePath, "r");

  if(file == NULL) {
    printf("error opening file %s", filePath);
    exit(1);
  }

  unsigned char buffer;
  int current_offset = offset;
  while(fread(&buffer, 1, 1, file) > 0) {
    writeBus(current_offset, buffer, bus);
    current_offset++;
  }
}
