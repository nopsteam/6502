#include "cpu.h"

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