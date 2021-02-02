#include "constants.h"

struct OPCODE opcodes[151] = {
  { .instruction = "ADC", .hex = 0x69, .bytes = 2 },
  { .instruction = "ADC", .hex = 0x65, .bytes = 2 },
  { .instruction = "ADC", .hex = 0x75, .bytes = 2 },
  { .instruction = "ADC", .hex = 0x6D, .bytes = 3 },
  { .instruction = "ADC", .hex = 0x7D, .bytes = 3 },
  { .instruction = "ADC", .hex = 0x79, .bytes = 3 },
  { .instruction = "ADC", .hex = 0x61, .bytes = 2 },
  { .instruction = "ADC", .hex = 0x71, .bytes = 2 },

  { .instruction = "AND", .hex = 0x29, .bytes = 2 },
  { .instruction = "AND", .hex = 0x25, .bytes = 2 },
  { .instruction = "AND", .hex = 0x35, .bytes = 2 },
  { .instruction = "AND", .hex = 0x2D, .bytes = 3 },
  { .instruction = "AND", .hex = 0x3D, .bytes = 3 },
  { .instruction = "AND", .hex = 0x39, .bytes = 3 },
  { .instruction = "AND", .hex = 0x21, .bytes = 2 },
  { .instruction = "AND", .hex = 0x31, .bytes = 2 },

  { .instruction = "ASL", .hex = 0x0A, .bytes = 1 },
  { .instruction = "ASL", .hex = 0x06, .bytes = 2 },
  { .instruction = "ASL", .hex = 0x16, .bytes = 2 },
  { .instruction = "ASL", .hex = 0x0E, .bytes = 3 },
  { .instruction = "ASL", .hex = 0x1E, .bytes = 3 },

  { .instruction = "BCC", .hex = 0x90, .bytes = 2 },
  { .instruction = "BCS", .hex = 0xB0, .bytes = 2 },

  { .instruction = "BEQ", .hex = 0xF0, .bytes = 2 },

  { .instruction = "BIT", .hex = 0x24, .bytes = 2 },
  { .instruction = "BIT", .hex = 0x2C, .bytes = 3 },

  { .instruction = "BMI", .hex = 0x30, .bytes = 2 },

  { .instruction = "BNE", .hex = 0xD0, .bytes = 2 },

  { .instruction = "BPL", .hex = 0x10, .bytes = 2 },

  { .instruction = "BRK", .hex = 0x00, .bytes = 1 },

  { .instruction = "BVC", .hex = 0x50, .bytes = 2 },
  { .instruction = "BVC", .hex = 0x70, .bytes = 2 },

  { .instruction = "CLC", .hex = 0x18, .bytes = 1 },

  { .instruction = "CLD", .hex = 0xD8, .bytes = 1 },

  { .instruction = "CLI", .hex = 0x58, .bytes = 1 },

  { .instruction = "CLV", .hex = 0xB8, .bytes = 1 },

  { .instruction = "CMP", .hex = 0xC9, .bytes = 2 },
  { .instruction = "CMP", .hex = 0xC5, .bytes = 2 },
  { .instruction = "CMP", .hex = 0xD5, .bytes = 2 },
  { .instruction = "CMP", .hex = 0xCD, .bytes = 3 },
  { .instruction = "CMP", .hex = 0xDD, .bytes = 3 },
  { .instruction = "CMP", .hex = 0xD9, .bytes = 3 },
  { .instruction = "CMP", .hex = 0xC1, .bytes = 2 },
  { .instruction = "CMP", .hex = 0xD1, .bytes = 2 },

  { .instruction = "CPX", .hex = 0xE0, .bytes = 2 },
  { .instruction = "CPX", .hex = 0xE4, .bytes = 2 },
  { .instruction = "CPX", .hex = 0xEC, .bytes = 3 },

  { .instruction = "CPY", .hex = 0xC0, .bytes = 2 },
  { .instruction = "CPY", .hex = 0xC4, .bytes = 2 },
  { .instruction = "CPY", .hex = 0xCC, .bytes = 3 },

  { .instruction = "DEC", .hex = 0xC6, .bytes = 2 },
  { .instruction = "DEC", .hex = 0xD6, .bytes = 2 },
  { .instruction = "DEC", .hex = 0xCE, .bytes = 3 },
  { .instruction = "DEC", .hex = 0xDE, .bytes = 3 },
  { .instruction = "DEC", .hex = 0xCA, .bytes = 1 },
  { .instruction = "DEC", .hex = 0x88, .bytes = 1 },

  { .instruction = "EOR", .hex = 0x49, .bytes = 2 },
  { .instruction = "EOR", .hex = 0x45, .bytes = 2 },
  { .instruction = "EOR", .hex = 0x55, .bytes = 2 },
  { .instruction = "EOR", .hex = 0x4D, .bytes = 3 },
  { .instruction = "EOR", .hex = 0x5D, .bytes = 3 },
  { .instruction = "EOR", .hex = 0x59, .bytes = 3 },
  { .instruction = "EOR", .hex = 0x41, .bytes = 2 },
  { .instruction = "EOR", .hex = 0x51, .bytes = 2 },

  { .instruction = "INC", .hex = 0xE6, .bytes = 2 },
  { .instruction = "INC", .hex = 0xF6, .bytes = 2 },
  { .instruction = "INC", .hex = 0xEE, .bytes = 3 },
  { .instruction = "INC", .hex = 0xFE, .bytes = 3 },

  { .instruction = "INX", .hex = 0xE8, .bytes = 1 },

  { .instruction = "INY", .hex = 0xC8, .bytes = 1 },

  { .instruction = "JMP", .hex = 0x4C, .bytes = 3 },
  { .instruction = "JMP", .hex = 0x6C, .bytes = 3 },

  { .instruction = "JSR", .hex = 0x20, .bytes = 3 },

  { .instruction = "LDA", .hex = 0xA9, .bytes = 2 },
  { .instruction = "LDA", .hex = 0xA5, .bytes = 2 },
  { .instruction = "LDA", .hex = 0xB5, .bytes = 2 },
  { .instruction = "LDA", .hex = 0xAD, .bytes = 3 },
  { .instruction = "LDA", .hex = 0xBD, .bytes = 3 },
  { .instruction = "LDA", .hex = 0xB9, .bytes = 3 },
  { .instruction = "LDA", .hex = 0xA1, .bytes = 2 },
  { .instruction = "LDA", .hex = 0xB1, .bytes = 2 },

  { .instruction = "LDX", .hex = 0xA2, .bytes = 2 },
  { .instruction = "LDX", .hex = 0xA6, .bytes = 2 },
  { .instruction = "LDX", .hex = 0xB6, .bytes = 2 },
  { .instruction = "LDX", .hex = 0xAE, .bytes = 3 },
  { .instruction = "LDX", .hex = 0xBE, .bytes = 3 },

  { .instruction = "LDY", .hex = 0xA0, .bytes = 2 },
  { .instruction = "LDY", .hex = 0xA4, .bytes = 2 },
  { .instruction = "LDY", .hex = 0xB4, .bytes = 2 },
  { .instruction = "LDY", .hex = 0xAC, .bytes = 3 },
  { .instruction = "LDY", .hex = 0xBC, .bytes = 3 },

  { .instruction = "LSR", .hex = 0x4A, .bytes = 1 },
  { .instruction = "LSR", .hex = 0x46, .bytes = 2 },
  { .instruction = "LSR", .hex = 0x56, .bytes = 2 },
  { .instruction = "LSR", .hex = 0x4E, .bytes = 3 },
  { .instruction = "LSR", .hex = 0x5E, .bytes = 3 },

  { .instruction = "NOP", .hex = 0xEA, .bytes = 1 },

  { .instruction = "ORA", .hex = 0x09, .bytes = 2 },
  { .instruction = "ORA", .hex = 0x05, .bytes = 2 },
  { .instruction = "ORA", .hex = 0x15, .bytes = 2 },
  { .instruction = "ORA", .hex = 0x0D, .bytes = 3 },
  { .instruction = "ORA", .hex = 0x1D, .bytes = 3 },
  { .instruction = "ORA", .hex = 0x19, .bytes = 3 },
  { .instruction = "ORA", .hex = 0x01, .bytes = 2 },
  { .instruction = "ORA", .hex = 0x11, .bytes = 2 },

  { .instruction = "PHA", .hex = 0x48, .bytes = 1 },

  { .instruction = "PHP", .hex = 0x08, .bytes = 1 },

  { .instruction = "PLA", .hex = 0x68, .bytes = 1 },

  { .instruction = "PLP", .hex = 0x28, .bytes = 1 },

  { .instruction = "ROL", .hex = 0x2A, .bytes = 1 },
  { .instruction = "ROL", .hex = 0x26, .bytes = 2 },
  { .instruction = "ROL", .hex = 0x36, .bytes = 2 },
  { .instruction = "ROL", .hex = 0x2E, .bytes = 3 },
  { .instruction = "ROL", .hex = 0x3E, .bytes = 3 },

  { .instruction = "ROR", .hex = 0x6A, .bytes = 1 },
  { .instruction = "ROR", .hex = 0x66, .bytes = 2 },
  { .instruction = "ROR", .hex = 0x76, .bytes = 2 },
  { .instruction = "ROR", .hex = 0x6E, .bytes = 3 },
  { .instruction = "ROR", .hex = 0x7E, .bytes = 3 },

  { .instruction = "RTI", .hex = 0x40, .bytes = 1 },

  { .instruction = "RTS", .hex = 0x60, .bytes = 1 },

  { .instruction = "SBC", .hex = 0xE9, .bytes = 2 },
  { .instruction = "SBC", .hex = 0xE5, .bytes = 2 },
  { .instruction = "SBC", .hex = 0xF5, .bytes = 2 },
  { .instruction = "SBC", .hex = 0xED, .bytes = 3 },
  { .instruction = "SBC", .hex = 0xFD, .bytes = 3 },
  { .instruction = "SBC", .hex = 0xF9, .bytes = 3 },
  { .instruction = "SBC", .hex = 0xE1, .bytes = 2 },
  { .instruction = "SBC", .hex = 0xF1, .bytes = 2 },

  { .instruction = "SEC", .hex = 0x38, .bytes = 1 },

  { .instruction = "SED", .hex = 0xF8, .bytes = 1 },

  { .instruction = "SEI", .hex = 0x78, .bytes = 1 },

  { .instruction = "STA", .hex = 0x85, .bytes = 2 },
  { .instruction = "STA", .hex = 0x95, .bytes = 2 },
  { .instruction = "STA", .hex = 0x8D, .bytes = 3 },
  { .instruction = "STA", .hex = 0x9D, .bytes = 3 },
  { .instruction = "STA", .hex = 0x99, .bytes = 3 },
  { .instruction = "STA", .hex = 0x81, .bytes = 2 },
  { .instruction = "STA", .hex = 0x91, .bytes = 2 },

  { .instruction = "STX", .hex = 0x86, .bytes = 2 },
  { .instruction = "STX", .hex = 0x96, .bytes = 2 },
  { .instruction = "STX", .hex = 0x8E, .bytes = 3 },

  { .instruction = "STY", .hex = 0x84, .bytes = 2 },
  { .instruction = "STY", .hex = 0x94, .bytes = 2 },
  { .instruction = "STY", .hex = 0x8C, .bytes = 3 },

  { .instruction = "TAX", .hex = 0xAA, .bytes = 1 },

  { .instruction = "TAY", .hex = 0xA8, .bytes = 1 },

  { .instruction = "TSX", .hex = 0xBA, .bytes = 1 },

  { .instruction = "TXA", .hex = 0x8A, .bytes = 1 },

  { .instruction = "TXS", .hex = 0x9A, .bytes = 1 },
  
  { .instruction = "TYA", .hex = 0x98, .bytes = 1 }
};
