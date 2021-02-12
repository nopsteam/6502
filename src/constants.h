enum ADDRESSING_MODE_INDEX {
  Implied = 0,
  Accumulator = 1,
  Immediate = 2,
  ZeroPage = 3,
  ZeroPageX = 4,
  ZeroPageY = 5,
  Relative = 6,
  Absolute = 7,
  AbsoluteX = 8,
  AbsoluteY = 9,
  Indirect = 10,
  IndirectX = 11,
  IndirectY = 12
};

struct ADDRESSING_MODE {
  int index;
  int length;
};

struct OPCODE {
  char * instruction;
  char hex;
  struct ADDRESSING_MODE * addressing;
};

struct PROGRAM_LINE {
  struct OPCODE * opcode;
  char args[3];
};

struct PROGRAM {
  struct PROGRAM_LINE * program;
  int lines;
};

extern enum ADDRESSING_MODE_INDEX addressing;
extern struct ADDRESSING_MODE addressing_modes[13];
extern struct OPCODE opcodes[151];
