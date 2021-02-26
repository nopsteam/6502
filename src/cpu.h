#include <stdbool.h>
#include "bus.h"

struct STATUS {
  bool carry;
  bool zero;
  bool interrupt;
  bool decimal;
  bool break_cmd;
  bool overflow;
  bool negative;
};

struct CPU {
  unsigned char accumulator;
  unsigned char index_x;
  unsigned char index_y;
  unsigned char stack_pointer;
  unsigned int  pc;
  struct STATUS status;
};

void resetCpu(struct CPU * cpu, struct BUS * bus);
void clockCpu(struct CPU * cpu, struct BUS * bus);
