#include "opcodes.h"

const int stackEndAddress = 0x100; 

void pushStack(struct CPU *cpu, struct BUS *bus, unsigned char value) {
  writeBus(stackEndAddress + cpu->stack_pointer, value, bus);
  cpu->stack_pointer--;
}

unsigned char popStack(struct CPU *cpu, struct BUS *bus) {
  cpu->stack_pointer++;
  return readBus(stackEndAddress + cpu->stack_pointer, bus);
}

int hexToDecimalMode(unsigned char hex) {
  int hi = ((hex & 0xF0) >> 4);
  if (hi > 9) hi = hi % 9;
  int lo = hex & 0xF;
  if (lo > 9) lo = lo % 9;
  return (hi * 10) + lo;
}

bool isAccumulatorAddressMode(unsigned int address) {
  return address == 0;
}

unsigned char readFromMemoryOrAccumulator(unsigned int address, struct CPU *cpu, struct BUS *bus) {
  return isAccumulatorAddressMode(address)
    ? cpu->accumulator
    : readBus(address, bus);
}

void writeOnMemoryOrAccumulator(unsigned int address, unsigned char result, struct CPU *cpu, struct BUS *bus) {
  isAccumulatorAddressMode(address)
    ? cpu->accumulator = result
    : writeBus(address, result, bus);
}

void aslOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  unsigned char current = readFromMemoryOrAccumulator(address, cpu, bus);
  unsigned char result = current << 1;

  cpu->status.carry = current & 0x80;
  cpu->status.negative = result >> 7;
  cpu->status.zero = result == 0x00;

  writeOnMemoryOrAccumulator(address, result, cpu, bus);
}

void bccOpcode(unsigned int address, struct CPU *cpu)
{
  if (!cpu->status.carry) cpu->pc = address;
}

void bcsOpcode(unsigned int address, struct CPU *cpu)
{
  if (cpu->status.carry) cpu->pc = address;
}

void beqOpcode(unsigned int address, struct CPU *cpu)
{
  if (cpu->status.zero) cpu->pc = address;
}

void bitOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  signed int compareResult = readBus(address, bus);
  cpu->status.negative = (compareResult >> 7);
  cpu->status.overflow = (compareResult >> 6) & 1;
  cpu->status.zero = (cpu->accumulator & (unsigned char)compareResult) == 0;
}

void bmiOpcode(unsigned int address, struct CPU *cpu)
{
  if (cpu->status.negative) cpu->pc = address;
}

void bneOpcode(unsigned int address, struct CPU *cpu)
{
  if (!cpu->status.zero) cpu->pc = address;
}

void bplOpcode(unsigned int address, struct CPU *cpu)
{
  if (!cpu->status.negative) cpu->pc = address;
}

void bvcOpcode(unsigned int address, struct CPU *cpu)
{
  if (!cpu->status.overflow) cpu->pc = address;
}

void bvsOpcode(unsigned int address, struct CPU *cpu)
{
  if (cpu->status.overflow) cpu->pc = address;
}

void cpyOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  signed int compareResult = cpu->index_y - readBus(address, bus);
  cpu->status.carry = compareResult >= 0;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void inxOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->index_x++;
  signed int compareResult = (signed char)cpu->index_x;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void inyOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->index_y++;
  signed int compareResult = (signed char)cpu->index_y;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void jmpOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->pc = address;
}

void jsrOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  cpu->pc--;
  pushStack(cpu, bus, (cpu->pc >> 8));
  pushStack(cpu, bus, cpu->pc);
  cpu->pc = address;
}

void ldaOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  cpu->accumulator = readBus(address, bus);
  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void ldxOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  cpu->index_x = bus->memory[address]; //TODO: use readBus
  signed int compareResult = (signed char)cpu->index_x;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void ldyOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  cpu->index_y = bus->memory[address]; //TODO: use readBus
  signed int compareResult = (signed char)cpu->index_y;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void lsrOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  unsigned char current = readFromMemoryOrAccumulator(address, cpu, bus);
  unsigned char result = current >> 1;

  cpu->status.carry = current & 0x01;
  cpu->status.negative = result >> 7;
  cpu->status.zero = result == 0x00;

  writeOnMemoryOrAccumulator(address, result, cpu, bus);
}

void nopOpcode()
{
  // nopsteam!ftw
}

void phaOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  pushStack(cpu, bus, cpu->accumulator);
}

void rolOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  unsigned char current = readFromMemoryOrAccumulator(address, cpu, bus);
  unsigned char result = (current << 1) | cpu->status.carry;

  cpu->status.carry = current & 0x80;
  cpu->status.negative = result >> 7;
  cpu->status.zero = result == 0x00;

  writeOnMemoryOrAccumulator(address, result, cpu, bus);
}

void rtsOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  unsigned char lo = popStack(cpu, bus);
  unsigned char hi = popStack(cpu, bus);
  cpu->pc = (hi << 8) | lo;
  cpu->pc++;
}

void staOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  writeBus(address, cpu->accumulator, bus);
}

void stxOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  writeBus(address, cpu->index_x, bus);
}

void styOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  writeBus(address, cpu->index_y, bus);
}

void txaOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->accumulator = cpu->index_x;
  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void txsOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->stack_pointer = cpu->index_x;
}

void tyaOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  cpu->accumulator = cpu->index_y;
  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}
