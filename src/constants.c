#include "constants.h"

struct ADDRESSING_MODE addressing_modes[13] = {
  {.name = "Implied", .length = 1},
  {.name = "Accumulator", .length = 1},
  {.name = "Immediate", .length = 2},
  {.name = "ZeroPage", .length = 2},
  {.name = "ZeroPageX", .length = 2},
  {.name = "ZeroPageY", .length = 2},
  {.name = "Relative", .length = 2},
  {.name = "Absolute", .length = 3},
  {.name = "AbsoluteX", .length = 3},
  {.name = "AbsoluteY", .length = 3},
  {.name = "Indirect", .length = 3},
  {.name = "IndirectX", .length = 2},
  {.name = "IndirectY", .length = 2}
};

struct OPCODE opcodes[151] = {
  { .instruction = "ADC", .hex = 0x69, .addressing = &addressing_modes[Immediate] },
  { .instruction = "ADC", .hex = 0x65, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "ADC", .hex = 0x75, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "ADC", .hex = 0x6D, .addressing = &addressing_modes[Absolute] },
  { .instruction = "ADC", .hex = 0x7D, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "ADC", .hex = 0x79, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "ADC", .hex = 0x61, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "ADC", .hex = 0x71, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "AND", .hex = 0x29, .addressing = &addressing_modes[Immediate] },
  { .instruction = "AND", .hex = 0x25, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "AND", .hex = 0x35, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "AND", .hex = 0x2D, .addressing = &addressing_modes[Absolute] },
  { .instruction = "AND", .hex = 0x3D, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "AND", .hex = 0x39, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "AND", .hex = 0x21, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "AND", .hex = 0x31, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "ASL", .hex = 0x0A, .addressing = &addressing_modes[Accumulator] },
  { .instruction = "ASL", .hex = 0x06, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "ASL", .hex = 0x16, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "ASL", .hex = 0x0E, .addressing = &addressing_modes[Absolute] },
  { .instruction = "ASL", .hex = 0x1E, .addressing = &addressing_modes[AbsoluteX] },

  { .instruction = "BCC", .hex = 0x90, .addressing = &addressing_modes[Relative] },
  { .instruction = "BCS", .hex = 0xB0, .addressing = &addressing_modes[Relative] },

  { .instruction = "BEQ", .hex = 0xF0, .addressing = &addressing_modes[Relative] },

  { .instruction = "BIT", .hex = 0x24, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "BIT", .hex = 0x2C, .addressing = &addressing_modes[Absolute] },

  { .instruction = "BMI", .hex = 0x30, .addressing = &addressing_modes[Relative] },

  { .instruction = "BNE", .hex = 0xD0, .addressing = &addressing_modes[Relative] },

  { .instruction = "BPL", .hex = 0x10, .addressing = &addressing_modes[Relative] },

  { .instruction = "BRK", .hex = 0x00, .addressing = &addressing_modes[Implied] },

  { .instruction = "BVC", .hex = 0x50, .addressing = &addressing_modes[Relative] },
  { .instruction = "BVC", .hex = 0x70, .addressing = &addressing_modes[Relative] },

  { .instruction = "CLC", .hex = 0x18, .addressing = &addressing_modes[Implied] },

  { .instruction = "CLD", .hex = 0xD8, .addressing = &addressing_modes[Implied] },

  { .instruction = "CLI", .hex = 0x58, .addressing = &addressing_modes[Implied] },

  { .instruction = "CLV", .hex = 0xB8, .addressing = &addressing_modes[Implied] },

  { .instruction = "CMP", .hex = 0xC9, .addressing = &addressing_modes[Immediate] },
  { .instruction = "CMP", .hex = 0xC5, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "CMP", .hex = 0xD5, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "CMP", .hex = 0xCD, .addressing = &addressing_modes[Absolute] },
  { .instruction = "CMP", .hex = 0xDD, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "CMP", .hex = 0xD9, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "CMP", .hex = 0xC1, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "CMP", .hex = 0xD1, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "CPX", .hex = 0xE0, .addressing = &addressing_modes[Immediate] },
  { .instruction = "CPX", .hex = 0xE4, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "CPX", .hex = 0xEC, .addressing = &addressing_modes[Absolute] },

  { .instruction = "CPY", .hex = 0xC0, .addressing = &addressing_modes[Immediate] },
  { .instruction = "CPY", .hex = 0xC4, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "CPY", .hex = 0xCC, .addressing = &addressing_modes[Absolute] },

  { .instruction = "DEC", .hex = 0xC6, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "DEC", .hex = 0xD6, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "DEC", .hex = 0xCE, .addressing = &addressing_modes[Absolute] },
  { .instruction = "DEC", .hex = 0xDE, .addressing = &addressing_modes[AbsoluteX] },

  { .instruction = "DEX", .hex = 0xCA, .addressing = &addressing_modes[Implied] },
  { .instruction = "DEY", .hex = 0x88, .addressing = &addressing_modes[Implied] },

  { .instruction = "EOR", .hex = 0x49, .addressing = &addressing_modes[Immediate] },
  { .instruction = "EOR", .hex = 0x45, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "EOR", .hex = 0x55, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "EOR", .hex = 0x4D, .addressing = &addressing_modes[Absolute] },
  { .instruction = "EOR", .hex = 0x5D, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "EOR", .hex = 0x59, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "EOR", .hex = 0x41, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "EOR", .hex = 0x51, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "INC", .hex = 0xE6, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "INC", .hex = 0xF6, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "INC", .hex = 0xEE, .addressing = &addressing_modes[Absolute] },
  { .instruction = "INC", .hex = 0xFE, .addressing = &addressing_modes[AbsoluteX] },

  { .instruction = "INX", .hex = 0xE8, .addressing = &addressing_modes[Implied] },
  { .instruction = "INY", .hex = 0xC8, .addressing = &addressing_modes[Implied] },

  { .instruction = "JMP", .hex = 0x4C, .addressing = &addressing_modes[Absolute] },
  { .instruction = "JMP", .hex = 0x6C, .addressing = &addressing_modes[Indirect] },

  { .instruction = "JSR", .hex = 0x20, .addressing = &addressing_modes[Absolute] },

  { .instruction = "LDA", .hex = 0xA9, .addressing = &addressing_modes[Immediate] },
  { .instruction = "LDA", .hex = 0xA5, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "LDA", .hex = 0xB5, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "LDA", .hex = 0xAD, .addressing = &addressing_modes[Absolute] },
  { .instruction = "LDA", .hex = 0xBD, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "LDA", .hex = 0xB9, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "LDA", .hex = 0xA1, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "LDA", .hex = 0xB1, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "LDX", .hex = 0xA2, .addressing = &addressing_modes[Immediate] },
  { .instruction = "LDX", .hex = 0xA6, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "LDX", .hex = 0xB6, .addressing = &addressing_modes[ZeroPageY] },
  { .instruction = "LDX", .hex = 0xAE, .addressing = &addressing_modes[Absolute] },
  { .instruction = "LDX", .hex = 0xBE, .addressing = &addressing_modes[AbsoluteY] },

  { .instruction = "LDY", .hex = 0xA0, .addressing = &addressing_modes[Immediate] },
  { .instruction = "LDY", .hex = 0xA4, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "LDY", .hex = 0xB4, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "LDY", .hex = 0xAC, .addressing = &addressing_modes[Absolute] },
  { .instruction = "LDY", .hex = 0xBC, .addressing = &addressing_modes[AbsoluteX] },

  { .instruction = "LSR", .hex = 0x4A, .addressing = &addressing_modes[Accumulator] },
  { .instruction = "LSR", .hex = 0x46, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "LSR", .hex = 0x56, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "LSR", .hex = 0x4E, .addressing = &addressing_modes[Absolute] },
  { .instruction = "LSR", .hex = 0x5E, .addressing = &addressing_modes[AbsoluteX] },

  { .instruction = "NOP", .hex = 0xEA, .addressing = &addressing_modes[Implied] },

  { .instruction = "ORA", .hex = 0x09, .addressing = &addressing_modes[Immediate] },
  { .instruction = "ORA", .hex = 0x05, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "ORA", .hex = 0x15, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "ORA", .hex = 0x0D, .addressing = &addressing_modes[Absolute] },
  { .instruction = "ORA", .hex = 0x1D, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "ORA", .hex = 0x19, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "ORA", .hex = 0x01, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "ORA", .hex = 0x11, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "PHA", .hex = 0x48, .addressing = &addressing_modes[Implied] },

  { .instruction = "PHP", .hex = 0x08, .addressing = &addressing_modes[Implied] },

  { .instruction = "PLA", .hex = 0x68, .addressing = &addressing_modes[Implied] },

  { .instruction = "PLP", .hex = 0x28, .addressing = &addressing_modes[Implied] },

  { .instruction = "ROL", .hex = 0x2A, .addressing = &addressing_modes[Accumulator] },
  { .instruction = "ROL", .hex = 0x26, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "ROL", .hex = 0x36, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "ROL", .hex = 0x2E, .addressing = &addressing_modes[Absolute] },
  { .instruction = "ROL", .hex = 0x3E, .addressing = &addressing_modes[AbsoluteX] },

  { .instruction = "ROR", .hex = 0x6A, .addressing = &addressing_modes[Accumulator] },
  { .instruction = "ROR", .hex = 0x66, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "ROR", .hex = 0x76, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "ROR", .hex = 0x6E, .addressing = &addressing_modes[Absolute] },
  { .instruction = "ROR", .hex = 0x7E, .addressing = &addressing_modes[AbsoluteX] },

  { .instruction = "RTI", .hex = 0x40, .addressing = &addressing_modes[Implied] },

  { .instruction = "RTS", .hex = 0x60, .addressing = &addressing_modes[Implied] },

  { .instruction = "SBC", .hex = 0xE9, .addressing = &addressing_modes[Immediate] },
  { .instruction = "SBC", .hex = 0xE5, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "SBC", .hex = 0xF5, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "SBC", .hex = 0xED, .addressing = &addressing_modes[Absolute] },
  { .instruction = "SBC", .hex = 0xFD, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "SBC", .hex = 0xF9, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "SBC", .hex = 0xE1, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "SBC", .hex = 0xF1, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "SEC", .hex = 0x38, .addressing = &addressing_modes[Implied] },

  { .instruction = "SED", .hex = 0xF8, .addressing = &addressing_modes[Implied] },

  { .instruction = "SEI", .hex = 0x78, .addressing = &addressing_modes[Implied] },

  { .instruction = "STA", .hex = 0x85, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "STA", .hex = 0x95, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "STA", .hex = 0x8D, .addressing = &addressing_modes[Absolute] },
  { .instruction = "STA", .hex = 0x9D, .addressing = &addressing_modes[AbsoluteX] },
  { .instruction = "STA", .hex = 0x99, .addressing = &addressing_modes[AbsoluteY] },
  { .instruction = "STA", .hex = 0x81, .addressing = &addressing_modes[IndirectX] },
  { .instruction = "STA", .hex = 0x91, .addressing = &addressing_modes[IndirectY] },

  { .instruction = "STX", .hex = 0x86, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "STX", .hex = 0x96, .addressing = &addressing_modes[ZeroPageY] },
  { .instruction = "STX", .hex = 0x8E, .addressing = &addressing_modes[Absolute] },

  { .instruction = "STY", .hex = 0x84, .addressing = &addressing_modes[ZeroPage] },
  { .instruction = "STY", .hex = 0x94, .addressing = &addressing_modes[ZeroPageX] },
  { .instruction = "STY", .hex = 0x8C, .addressing = &addressing_modes[Absolute] },

  { .instruction = "TAX", .hex = 0xAA, .addressing = &addressing_modes[Implied] },

  { .instruction = "TAY", .hex = 0xA8, .addressing = &addressing_modes[Implied] },

  { .instruction = "TSX", .hex = 0xBA, .addressing = &addressing_modes[Implied] },

  { .instruction = "TXA", .hex = 0x8A, .addressing = &addressing_modes[Implied] },

  { .instruction = "TXS", .hex = 0x9A, .addressing = &addressing_modes[Implied] },

  { .instruction = "TYA", .hex = 0x98, .addressing = &addressing_modes[Implied] }
};
