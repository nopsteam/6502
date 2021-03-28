#include <stdio.h>
#include "constants.h"
#include "disassembler.h"
#include "opcodes.h"

const int stackEndAddress = 0x100; 

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

int clockCpu(struct CPU *cpu, struct BUS *bus) {
  struct OPCODE * opcode = NULL;
  opcode = GetOpcode(readBus(cpu->pc, bus));
  cpu->pc++;

  if (opcode) {
    unsigned int address = getAddressByOpcode(opcode, cpu, bus);

    switch (opcode->instruction->index) {
      case BCC:
        bccOpcode(address, cpu);
        break;
      case BCS:
        bcsOpcode(address, cpu);
        break;
      case BEQ:
        beqOpcode(address, cpu);
        break;
      case BIT:
        bitOpcode(address, cpu, bus);
        break;
      case BMI:
        bmiOpcode(address, cpu);
        break;
      case BNE:
        bneOpcode(address, cpu);
        break;
      case BPL:
        bplOpcode(address, cpu);
        break;
      case BVC:
        bvcOpcode(address, cpu);
        break;
      case BVS:
        bvsOpcode(address, cpu);
        break;
      case CPY: 
        cpyOpcode(address, cpu, bus);
        break;
      case INX:
        inxOpcode(address, cpu);
        break;
      case INY:
        inyOpcode(address, cpu);
        break;
      case JMP:
        jmpOpcode(address, cpu);
        break;
      case JSR:
        jsrOpcode(address, cpu, bus);
        break;
      case LDA:
        ldaOpcode(address, cpu, bus);
        break;
      case LDX:
        ldxOpcode(address, cpu, bus);
        break;
      case LDY:
        ldyOpcode(address, cpu, bus);
        break;
      case NOP:
        nopOpcode();
        break;
      case PHA:
        phaOpcode(address, cpu, bus);
        break;
      case RTS:
        rtsOpcode(address, cpu, bus);
        break;
      case STA:
        staOpcode(address, cpu, bus);
        break;
      case STX:
        stxOpcode(address, cpu, bus);
        break;
      case STY:
        styOpcode(address, cpu, bus);
        break;
      case TXA: 
        txaOpcode(address, cpu);
        break;
      case TXS:
        txsOpcode(address, cpu);
        break;
      case TYA:
        tyaOpcode(address, cpu, bus);
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
