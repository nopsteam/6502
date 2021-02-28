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

unsigned int zeroPageAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = readBus(cpu->pc, bus);
  cpu->pc++;
  return address & 0x00FF;
}

unsigned int zeroPageXAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = readBus(cpu->pc, bus);
  cpu->pc++;
  return address + cpu->index_x;
}

unsigned int zeroPageYAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = readBus(cpu->pc, bus);
  cpu->pc++;
  return address + cpu->index_y;
}

unsigned int absoluteAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned char lo = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned char hi = readBus(cpu->pc, bus);
  cpu->pc++;
  return (hi << 8) | lo;
}

unsigned int absoluteXAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned char lo = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned char hi = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned int address = (hi << 8) | lo;
  return address + cpu->index_x;
}

unsigned int absoluteYAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned char lo = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned char hi = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned int address = (hi << 8) | lo;
  return address + cpu->index_y;
}

unsigned int indirectXAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int base = readBus(cpu->pc, bus) + cpu->index_x;
  cpu->pc++;
  unsigned char lo = readBus(base, bus);
  unsigned char hi = readBus(base+1, bus);
  unsigned int address = (hi << 8) | lo;
  return address;
}

unsigned int indirectYAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int base = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned char lo = readBus(base, bus);
  unsigned char hi = readBus(base+1, bus);
  unsigned int address = (hi << 8) | lo;
  return address + cpu->index_y;
}

void staZeroPage(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = zeroPageAddressMode(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
  return;
}

void staZeroPageX(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = zeroPageXAddressMode(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
  return;
}

void staAbsolute(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = absoluteAddressMode(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
  return;
}

void staAbsoluteX(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = absoluteXAddressMode(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
  return;
}

void staAbsoluteY(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = absoluteYAddressMode(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
  return;
}

void staIndirectX(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = indirectXAddressMode(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
  return;
}

void staIndirectY(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = indirectYAddressMode(cpu, bus);
  writeBus(address, cpu->accumulator, bus);
  return;
}

void clockCpu(struct CPU *cpu, struct BUS *bus) {
  struct OPCODE * opcode = NULL;
  opcode = GetOpcode(readBus(cpu->pc, bus));
  cpu->pc++;

  if (opcode) {
    switch (opcode->hex) {
      case 0x85:
        staZeroPage(cpu, bus);
        break;
      case 0x95:
        staZeroPageX(cpu, bus);
        break;
      case 0x8D:
        staAbsolute(cpu, bus);
        break;
      case 0x9D:
        staAbsoluteX(cpu, bus);
        break;
      case 0x99:
        staAbsoluteY(cpu, bus);
        break;
      case 0x81:
        staIndirectX(cpu, bus);
        break;
      case 0x91:
        staIndirectY(cpu, bus);
        break;
      default:
        printf("NOT IMPLEMENTED YET... 0x%04x, %s \n", opcode->hex, opcode->instruction);
        break;
    }
  } else {
    printf("NOT IMPLEMENTED OPCODE: 0x%04x\n", readBus(cpu->pc -1, bus));
  }
}
