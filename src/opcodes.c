#include <stdio.h>
#include "opcodes.h"

void pushStack(struct CPU *cpu, struct BUS *bus, unsigned char value) {
  writeBus(STACK_END_ADDRESS + cpu->stack_pointer, value, bus);
  cpu->stack_pointer--;
}

unsigned char popStack(struct CPU *cpu, struct BUS *bus) {
  cpu->stack_pointer++;
  return readBus(STACK_END_ADDRESS + cpu->stack_pointer, bus);
}

int hexToDecimalMode(unsigned char hex) {
  int hi = ((hex & 0xF0) >> 4);
  if (hi > 9) hi = hi % 9;
  int lo = hex & 0xF;
  if (lo > 9) lo = lo % 9;
  return (hi * 10) + lo;
}

void setStatusByChar(unsigned char value, struct CPU *cpu) {
  cpu->status.carry = (value >> 0) & 0x1;
  cpu->status.zero = (value >> 1) & 0x1;
  cpu->status.interrupt = (value >> 2) & 0x1;
  cpu->status.decimal = (value >> 3) & 0x1;
  cpu->status.break_cmd = (value >> 4) & 0x1;
  cpu->status.overflow = (value >> 6) & 0x1;
  cpu->status.negative = (value >> 7) & 0x1;
}

unsigned char getStatusByChar(struct CPU *cpu) {
  return (cpu->status.negative << 7)
    | (cpu->status.overflow << 6)
    | (cpu->status.break_cmd << 4)
    | (cpu->status.decimal << 3)
    | (cpu->status.interrupt << 2)
    | (cpu->status.zero << 1)
    | (cpu->status.carry << 0);
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

void sumOperation(signed int value, struct CPU *cpu, struct BUS *bus) {
  signed int sum = cpu->accumulator + value + cpu->status.carry;
  cpu->status.carry = sum > 0xFF;
  cpu->status.overflow = ~(cpu->accumulator ^ value) & (cpu->accumulator ^ sum) & 0x80;
  cpu->accumulator = sum;
  cpu->status.negative = (cpu->accumulator >> 7);
  cpu->status.zero = cpu->accumulator == 0;
}

void adcOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus) {
  signed int valueFromAddress = readBus(address, bus);
  sumOperation(valueFromAddress, cpu, bus);
}

void sbcOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus) {
  signed int valueFromAddress = readBus(address, bus) ^ 0xFF;
  sumOperation(valueFromAddress, cpu, bus);
}

void andOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus) {
  cpu->accumulator = cpu->accumulator & readBus(address, bus);
  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
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

void clcOpcode(struct CPU *cpu) {
  cpu->status.carry = false;
}

void cldOpcode(struct CPU *cpu) {
  cpu->status.decimal = false;
}

void cliOpcode(struct CPU *cpu) {
  cpu->status.interrupt = false;
}

void clvOpcode(struct CPU *cpu) {
  cpu->status.overflow = false;
}

void cmpOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus) {
  signed int compareResult = cpu->accumulator - readBus(address, bus);
  cpu->status.carry = compareResult >= 0;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void cpxOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  signed int compareResult = cpu->index_x - readBus(address, bus);
  cpu->status.carry = compareResult >= 0;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void cpyOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  signed int compareResult = cpu->index_y - readBus(address, bus);
  cpu->status.carry = compareResult >= 0;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void decOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  signed int compareResult = (signed char)readBus(address, bus);
  compareResult--;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
  writeBus(address, compareResult, bus);
}

void dexOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->index_x--;
  signed int compareResult = (signed char)cpu->index_x;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void deyOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->index_y--;
  signed int compareResult = (signed char)cpu->index_y;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void eorOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus) {
  cpu->accumulator = cpu->accumulator ^ readBus(address, bus);
  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void incOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  signed int compareResult = (signed char)readBus(address, bus);
  compareResult++;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
  writeBus(address, compareResult, bus);
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
  cpu->index_x = readBus(address, bus);
  signed int compareResult = (signed char)cpu->index_x;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void ldyOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  cpu->index_y = readBus(address, bus);
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

void oraOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus) {
  cpu->accumulator = cpu->accumulator | readBus(address, bus);
  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void phaOpcode(struct CPU *cpu, struct BUS *bus)
{
  pushStack(cpu, bus, cpu->accumulator);
}

void phpOpcode(struct CPU *cpu, struct BUS *bus)
{
  pushStack(cpu, bus, getStatusByChar(cpu));
}

void plaOpcode(struct CPU *cpu, struct BUS *bus)
{
  cpu->accumulator = popStack(cpu, bus);

  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void plpOpcode(struct CPU *cpu, struct BUS *bus)
{
  char setBreakFlagFalse = ~0x10;
  unsigned char flagsValue = popStack(cpu, bus);
  setStatusByChar(flagsValue & setBreakFlagFalse, cpu);
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

void rorOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  unsigned char current = readFromMemoryOrAccumulator(address, cpu, bus);
  unsigned char result = (cpu->status.carry << 7) | (current >> 1);

  cpu->status.carry = current & 0x01;
  cpu->status.negative = result >> 7;
  cpu->status.zero = result == 0x00;

  writeOnMemoryOrAccumulator(address, result, cpu, bus);
}

void rtiOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  char setBreakFlagFalse = ~0x10;
  unsigned char flagsValue = popStack(cpu, bus);
  setStatusByChar(flagsValue & setBreakFlagFalse, cpu);

  unsigned char lo = popStack(cpu, bus);
  unsigned char hi = popStack(cpu, bus);
  cpu->pc = (hi << 8) | lo;
}

void rtsOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus)
{
  unsigned char lo = popStack(cpu, bus);
  unsigned char hi = popStack(cpu, bus);
  cpu->pc = (hi << 8) | lo;
  cpu->pc++;
}

void secOpcode(struct CPU *cpu) {
  cpu->status.carry = true;
}

void sedOpcode(struct CPU *cpu) {
  cpu->status.decimal = true;
}

void seiOpcode(struct CPU *cpu) {
  cpu->status.interrupt = true;
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

void taxOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->index_x = cpu->accumulator;
  signed int compareResult = (signed char)cpu->index_x;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void tayOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->index_y = cpu->accumulator;
  signed int compareResult = (signed char)cpu->index_y;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

void tsxOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->index_x = cpu->stack_pointer;
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

void tyaOpcode(unsigned int address, struct CPU *cpu)
{
  cpu->accumulator = cpu->index_y;
  signed int compareResult = (signed char)cpu->accumulator;
  cpu->status.zero = compareResult == 0;
  cpu->status.negative = compareResult < 0;
}

