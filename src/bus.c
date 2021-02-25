#include <stdio.h>
#include "bus.h"

struct BUS initialize() {
  struct BUS bus;

  bus.input = 0x00;

  for(int i = 0; i <= 1023; ++i)
  {
    bus.display[i] = 0x00;
  }

  for(int i = 0; i <= (64 * 1024); ++i)
  {
    bus.memory[i] = 0x00;
  }

  return bus;
}

void write(int addr, char data, struct BUS * bus) {
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

char read(int addr, struct BUS * bus) {
  char data = 0x00;

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
