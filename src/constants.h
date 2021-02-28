#include <stdbool.h>

enum OPCODE_TYPE_INDEX {
  ADC,
  AND,
  ASL,
  BCC,
  BCS,
  BEQ,
  BIT,
  BMI,
  BNE,
  BPL,
  BRK,
  BVC,
  BVS,
  CLC,
  CLD,
  CLI,
  CLV,
  CMP,
  CPX,
  CPY,
  DEC,
  DEX,
  DEY,
  EOR,
  INC,
  INX,
  INY,
  JMP,
  JSR,
  LDA,
  LDX,
  LDY,
  LSR,
  NOP,
  ORA,
  PHA,
  PHP,
  PLA,
  PLP,
  ROL,
  ROR,
  RTI,
  RTS,
  SBC,
  SEC,
  SED,
  SEI,
  STA,
  STX,
  STY,
  TAX,
  TAY,
  TSX,
  TXA,
  TXS,
  TYA
};

struct OPCODE_TYPE {
  int index;
  char * name;
};

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
  unsigned char hex;
  bool cycles_vary;
  int cycles;
  struct OPCODE_TYPE * instruction;
  struct ADDRESSING_MODE * addressing;
};

extern enum OPCODE_TYPE_INDEX opcode_type_index;
extern struct OPCODE_TYPE opcode_types[56];
extern struct OPCODE opcodes[151];
extern enum ADDRESSING_MODE_INDEX addressing;
extern struct ADDRESSING_MODE addressing_modes[13];
