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

unsigned int absoluteAddressMode(unsigned char index, struct CPU *cpu, struct BUS *bus) {
  unsigned char lo = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned char hi = readBus(cpu->pc, bus);
  cpu->pc++;
  return ((hi << 8) | lo) + index;
}

unsigned int immediateAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = cpu->pc;
  cpu->pc++;
  return address;
}

unsigned int indirect(unsigned int base_address, struct BUS *bus) {
  unsigned char lo = readBus(base_address, bus);
  unsigned char hi = readBus(base_address+1, bus);
  return (hi << 8) | lo;
}

unsigned int indirectAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int base_lo = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned int base_hi = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned int base = readBus((base_hi << 8) | base_lo, bus);
  unsigned int address = indirect(base, bus);
  return address;
}

unsigned int indirectXAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int base = readBus(cpu->pc, bus) + cpu->index_x;
  cpu->pc++;
  unsigned int address = indirect(base, bus);
  return address;
}

unsigned int indirectYAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int base = readBus(cpu->pc, bus);
  cpu->pc++;
  unsigned int address = indirect(base, bus);
  return address + cpu->index_y;
}

unsigned int relativeAddressMode(struct CPU *cpu, struct BUS *bus) {
  unsigned int address = cpu->pc + (signed char)readBus(cpu->pc, bus); 
  cpu->pc++;
  return address;
}

unsigned int zeroPageAddressMode(unsigned char index, struct CPU *cpu, struct BUS *bus) {
  unsigned int address = readBus(cpu->pc, bus);
  cpu->pc++;
  return address + index;
}

unsigned int getAddressByOpcode(struct OPCODE * opcode, struct CPU *cpu, struct BUS *bus) {
  switch (opcode->addressing->index) {
    case Absolute:
      return absoluteAddressMode(0, cpu, bus);
    case AbsoluteX:
      return absoluteAddressMode(cpu->index_x, cpu, bus);
    case AbsoluteY:
      return absoluteAddressMode(cpu->index_y, cpu, bus);
    case Immediate:
      return immediateAddressMode(cpu, bus);
    case Indirect:
      return indirectAddressMode(cpu, bus);
    case IndirectX:
      return indirectXAddressMode(cpu, bus);
    case IndirectY:
      return indirectYAddressMode(cpu, bus);
    case Relative:
      return relativeAddressMode(cpu, bus);
    case ZeroPage:
      return zeroPageAddressMode(0, cpu, bus);
    case ZeroPageX:
      return zeroPageAddressMode(cpu->index_x, cpu, bus);
    case ZeroPageY:
      return zeroPageAddressMode(cpu->index_y, cpu, bus);
    case Implied:
    default:
      return 0;
  }
}

void setZeroAndNegativeFlags(struct CPU *cpu, unsigned char data) {
  cpu->status.zero = data == 0;
  cpu->status.negative = (data >> 7) & 1;
}

void pushStack(struct CPU *cpu, struct BUS *bus, unsigned char value) {
  writeBus(0x0100 + cpu->stack_pointer, value, bus);
  cpu->stack_pointer--;
}

int clockCpu(struct CPU *cpu, struct BUS *bus) {
  struct OPCODE * opcode = NULL;
  opcode = GetOpcode(readBus(cpu->pc, bus));
  cpu->pc++;

  if (opcode) {
    unsigned int address = getAddressByOpcode(opcode, cpu, bus);
    signed int compareResult = 0;

    switch (opcode->instruction->index) {
      case STA:
        writeBus(address, cpu->accumulator, bus);
        break;
      case STX:
        writeBus(address, cpu->index_x, bus);
        break;
      case STY:
        writeBus(address, cpu->index_y, bus);
        break;
      case NOP:
        printf("let's slide!");
        break;
      case LDA:
        cpu->accumulator = readBus(address, bus);
        compareResult = (signed char)cpu->accumulator;
        cpu->status.zero = compareResult == 0;
        cpu->status.negative = compareResult < 0;
        break;
      case TXA: 
        cpu->accumulator = cpu->index_x;
        compareResult = (signed char)cpu->accumulator;
        cpu->status.zero = compareResult == 0;
        cpu->status.negative = compareResult < 0;
        break;
      case INX:
        cpu->index_x++;
        compareResult = (signed char)cpu->index_x;
        cpu->status.zero = compareResult == 0;
        cpu->status.negative = compareResult < 0;
        break;
      case INY:
        cpu->index_y++;
        compareResult = (signed char)cpu->index_y;
        cpu->status.zero = compareResult == 0;
        cpu->status.negative = compareResult < 0;
        break;
      case CPY: 
        compareResult = (signed char)cpu->index_y - readBus(address, bus);
        cpu->status.carry = compareResult >= 0;
        cpu->status.zero = compareResult == 0;
        cpu->status.negative = compareResult < 0;
        break;
      case PHA:
        pushStack(cpu, bus, cpu->accumulator);
        break;
      case LDY:
        cpu->index_y = bus->memory[address];
        compareResult = (signed char)cpu->index_y;
        cpu->status.zero = compareResult == 0;
        cpu->status.negative = compareResult < 0;
        break;
      case LDX:
        cpu->index_x = bus->memory[address];
        compareResult = (signed char)cpu->index_x;
        cpu->status.zero = compareResult == 0;
        cpu->status.negative = compareResult < 0;
        break;
      case BNE:
        if (!cpu->status.zero) cpu->pc = address;
        break;
      default:
        printf("NOT IMPLEMENTED YET... 0x%04x, %s \n", opcode->hex, opcode->instruction->name);
        break;
    }
  } else {
    printf("ERROR: INVALID OPCODE - 0x%04x\n", readBus(cpu->pc -1, bus));
    return 1;
  }

  return 0;
}
