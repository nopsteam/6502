#include <stdio.h>
#include "cpu.h"
#include "constants.h"
#include "disassembler.h"

void resetCpu(struct CPU * cpu, struct BUS * bus) {
  int reset_address_lo = 0xFFFC;
  int reset_address_hi = 0XFFFD;
  char lo = readBus(reset_address_lo, bus);
  char hi = readBus(reset_address_hi, bus);

  cpu->pc = (hi << 8) | lo;

  cpu->accumulator = 0;
  cpu->index_x = 0;
  cpu->index_y = 0;
  cpu->stack_pointer = 0xFD;

  cpu->status.carry = false;
  cpu->status.zero = false;
  cpu->status.interrupt = false;
  cpu->status.decimal = false;
  cpu->status.break_cmd = false;
  cpu->status.overflow = false;
  cpu->status.negative = false;
}

unsigned int addressingModesZeroPage(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = readBus(cpu->pc, bus);
  cpu->pc++;
  return address & 0x00FF;
}

void staZeroPage(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = addressingModesZeroPage(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
}

void clockCpu(struct CPU *cpu, struct BUS *bus) {
  struct OPCODE opcode = *GetOpcode(readBus(cpu->pc, bus));
  cpu->pc++;

  switch (opcode.hex) {
    case 0x85:
      staZeroPage(cpu, bus);
      break;
    default:
      printf("NOT IMPLEMENTED YET... %04x \n", opcode.hex);
      break;
  }
}
