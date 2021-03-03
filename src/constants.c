#include "constants.h"

struct OPCODE_TYPE opcode_types[56] = {
  {.index = ADC, .name = "ADC"},
  {.index = AND, .name = "AND"},
  {.index = ASL, .name = "ASL"},
  {.index = BCC, .name = "BCC"},
  {.index = BCS, .name = "BCS"},
  {.index = BEQ, .name = "BEQ"},
  {.index = BIT, .name = "BIT"},
  {.index = BMI, .name = "BMI"},
  {.index = BNE, .name = "BNE"},
  {.index = BPL, .name = "BPL"},
  {.index = BRK, .name = "BRK"},
  {.index = BVC, .name = "BVC"},
  {.index = BVS, .name = "BVS"},
  {.index = CLC, .name = "CLC"},
  {.index = CLD, .name = "CLD"},
  {.index = CLI, .name = "CLI"},
  {.index = CLV, .name = "CLV"},
  {.index = CMP, .name = "CMP"},
  {.index = CPX, .name = "CPX"},
  {.index = CPY, .name = "CPY"},
  {.index = DEC, .name = "DEC"},
  {.index = DEX, .name = "DEX"},
  {.index = DEY, .name = "DEY"},
  {.index = EOR, .name = "EOR"},
  {.index = INC, .name = "INC"},
  {.index = INX, .name = "INX"},
  {.index = INY, .name = "INY"},
  {.index = JMP, .name = "JMP"},
  {.index = JSR, .name = "JSR"},
  {.index = LDA, .name = "LDA"},
  {.index = LDX, .name = "LDX"},
  {.index = LDY, .name = "LDY"},
  {.index = LSR, .name = "LSR"},
  {.index = NOP, .name = "NOP"},
  {.index = ORA, .name = "ORA"},
  {.index = PHA, .name = "PHA"},
  {.index = PHP, .name = "PHP"},
  {.index = PLA, .name = "PLA"},
  {.index = PLP, .name = "PLP"},
  {.index = ROL, .name = "ROL"},
  {.index = ROR, .name = "ROR"},
  {.index = RTI, .name = "RTI"},
  {.index = RTS, .name = "RTS"},
  {.index = SBC, .name = "SBC"},
  {.index = SEC, .name = "SEC"},
  {.index = SED, .name = "SED"},
  {.index = SEI, .name = "SEI"},
  {.index = STA, .name = "STA"},
  {.index = STX, .name = "STX"},
  {.index = STY, .name = "STY"},
  {.index = TAX, .name = "TAX"},
  {.index = TAY, .name = "TAY"},
  {.index = TSX, .name = "TSX"},
  {.index = TXA, .name = "TXA"},
  {.index = TXS, .name = "TXS"},
  {.index = TYA, .name = "TYA"}
};

struct ADDRESSING_MODE addressing_modes[13] = {
  {.index = Implied, .length = 1},
  {.index = Accumulator, .length = 1},
  {.index = Immediate, .length = 2},
  {.index = ZeroPage, .length = 2},
  {.index = ZeroPageX, .length = 2},
  {.index = ZeroPageY, .length = 2},
  {.index = Relative, .length = 2},
  {.index = Absolute, .length = 3},
  {.index = AbsoluteX, .length = 3},
  {.index = AbsoluteY, .length = 3},
  {.index = Indirect, .length = 3},
  {.index = IndirectX, .length = 2},
  {.index = IndirectY, .length = 2}
};

struct OPCODE opcodes[151] = {
  {.instruction = &opcode_types[ADC], .hex = 0x69, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[ADC], .hex = 0x65, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[ADC], .hex = 0x75, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[ADC], .hex = 0x6D, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[ADC], .hex = 0x7D, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[ADC], .hex = 0x79, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[ADC], .hex = 0x61, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ADC], .hex = 0x71, .addressing = &addressing_modes[IndirectY],   .cycles = 5, .cycles_vary = true },

  {.instruction = &opcode_types[AND], .hex = 0x29, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[AND], .hex = 0x25, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[AND], .hex = 0x35, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[AND], .hex = 0x2D, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[AND], .hex = 0x3D, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[AND], .hex = 0x39, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[AND], .hex = 0x21, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[AND], .hex = 0x31, .addressing = &addressing_modes[IndirectY],   .cycles = 5, .cycles_vary = true },

  {.instruction = &opcode_types[ASL], .hex = 0x0A, .addressing = &addressing_modes[Accumulator], .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[ASL], .hex = 0x06, .addressing = &addressing_modes[ZeroPage],    .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[ASL], .hex = 0x16, .addressing = &addressing_modes[ZeroPageX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ASL], .hex = 0x0E, .addressing = &addressing_modes[Absolute],    .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ASL], .hex = 0x1E, .addressing = &addressing_modes[AbsoluteX],   .cycles = 7, .cycles_vary = false},

  {.instruction = &opcode_types[BCC], .hex = 0x90, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[BCS], .hex = 0xB0, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[BEQ], .hex = 0xF0, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[BIT], .hex = 0x24, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = true },
  {.instruction = &opcode_types[BIT], .hex = 0x2C, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = true },

  {.instruction = &opcode_types[BMI], .hex = 0x30, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[BNE], .hex = 0xD0, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[BPL], .hex = 0x10, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[BRK], .hex = 0x00, .addressing = &addressing_modes[Implied],     .cycles = 0, .cycles_vary = false},

  {.instruction = &opcode_types[BVC], .hex = 0x50, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[BVS], .hex = 0x70, .addressing = &addressing_modes[Relative],    .cycles = 2, .cycles_vary = true },

  {.instruction = &opcode_types[CLC], .hex = 0x18, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[CLD], .hex = 0xD8, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[CLI], .hex = 0x58, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[CLV], .hex = 0xB8, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[CMP], .hex = 0xC9, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[CMP], .hex = 0xC5, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[CMP], .hex = 0xD5, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[CMP], .hex = 0xCD, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[CMP], .hex = 0xDD, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[CMP], .hex = 0xD9, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[CMP], .hex = 0xC1, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[CMP], .hex = 0xD1, .addressing = &addressing_modes[IndirectY],   .cycles = 5, .cycles_vary = true },

  {.instruction = &opcode_types[CPX], .hex = 0xE0, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[CPX], .hex = 0xE4, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[CPX], .hex = 0xEC, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},

  {.instruction = &opcode_types[CPY], .hex = 0xC0, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[CPY], .hex = 0xC4, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[CPY], .hex = 0xCC, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},

  {.instruction = &opcode_types[DEC], .hex = 0xC6, .addressing = &addressing_modes[ZeroPage],    .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[DEC], .hex = 0xD6, .addressing = &addressing_modes[ZeroPageX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[DEC], .hex = 0xCE, .addressing = &addressing_modes[Absolute],    .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[DEC], .hex = 0xDE, .addressing = &addressing_modes[AbsoluteX],   .cycles = 7, .cycles_vary = false},

  {.instruction = &opcode_types[DEX], .hex = 0xCA, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[DEY], .hex = 0x88, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[EOR], .hex = 0x49, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[EOR], .hex = 0x45, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[EOR], .hex = 0x55, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[EOR], .hex = 0x4D, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[EOR], .hex = 0x5D, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[EOR], .hex = 0x59, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[EOR], .hex = 0x41, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[EOR], .hex = 0x51, .addressing = &addressing_modes[IndirectY],   .cycles = 5, .cycles_vary = true },

  {.instruction = &opcode_types[INC], .hex = 0xE6, .addressing = &addressing_modes[ZeroPage],    .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[INC], .hex = 0xF6, .addressing = &addressing_modes[ZeroPageX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[INC], .hex = 0xEE, .addressing = &addressing_modes[Absolute],    .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[INC], .hex = 0xFE, .addressing = &addressing_modes[AbsoluteX],   .cycles = 7, .cycles_vary = false},

  {.instruction = &opcode_types[INX], .hex = 0xE8, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[INY], .hex = 0xC8, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[JMP], .hex = 0x4C, .addressing = &addressing_modes[Absolute],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[JMP], .hex = 0x6C, .addressing = &addressing_modes[Indirect],    .cycles = 5, .cycles_vary = false},

  {.instruction = &opcode_types[JSR], .hex = 0x20, .addressing = &addressing_modes[Absolute],    .cycles = 6, .cycles_vary = false},

  {.instruction = &opcode_types[LDA], .hex = 0xA9, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[LDA], .hex = 0xA5, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[LDA], .hex = 0xB5, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[LDA], .hex = 0xAD, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[LDA], .hex = 0xBD, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[LDA], .hex = 0xB9, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[LDA], .hex = 0xA1, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[LDA], .hex = 0xB1, .addressing = &addressing_modes[IndirectY],   .cycles = 5, .cycles_vary = true },

  {.instruction = &opcode_types[LDX], .hex = 0xA2, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[LDX], .hex = 0xA6, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[LDX], .hex = 0xB6, .addressing = &addressing_modes[ZeroPageY],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[LDX], .hex = 0xAE, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[LDX], .hex = 0xBE, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },

  {.instruction = &opcode_types[LDY], .hex = 0xA0, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[LDY], .hex = 0xA4, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[LDY], .hex = 0xB4, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[LDY], .hex = 0xAC, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[LDY], .hex = 0xBC, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },

  {.instruction = &opcode_types[LSR], .hex = 0x4A, .addressing = &addressing_modes[Accumulator], .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[LSR], .hex = 0x46, .addressing = &addressing_modes[ZeroPage],    .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[LSR], .hex = 0x56, .addressing = &addressing_modes[ZeroPageX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[LSR], .hex = 0x4E, .addressing = &addressing_modes[Absolute],    .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[LSR], .hex = 0x5E, .addressing = &addressing_modes[AbsoluteX],   .cycles = 7, .cycles_vary = false},

  {.instruction = &opcode_types[NOP], .hex = 0xEA, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[ORA], .hex = 0x09, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[ORA], .hex = 0x05, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[ORA], .hex = 0x15, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[ORA], .hex = 0x0D, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[ORA], .hex = 0x1D, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[ORA], .hex = 0x19, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[ORA], .hex = 0x01, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ORA], .hex = 0x11, .addressing = &addressing_modes[IndirectY],   .cycles = 5, .cycles_vary = true },

  {.instruction = &opcode_types[PHA], .hex = 0x48, .addressing = &addressing_modes[Implied],     .cycles = 3, .cycles_vary = false},

  {.instruction = &opcode_types[PHP], .hex = 0x08, .addressing = &addressing_modes[Implied],     .cycles = 3, .cycles_vary = false},

  {.instruction = &opcode_types[PLA], .hex = 0x68, .addressing = &addressing_modes[Implied],     .cycles = 4, .cycles_vary = false},

  {.instruction = &opcode_types[PLP], .hex = 0x28, .addressing = &addressing_modes[Implied],     .cycles = 4, .cycles_vary = false},

  {.instruction = &opcode_types[ROL], .hex = 0x2A, .addressing = &addressing_modes[Accumulator], .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[ROL], .hex = 0x26, .addressing = &addressing_modes[ZeroPage],    .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[ROL], .hex = 0x36, .addressing = &addressing_modes[ZeroPageX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ROL], .hex = 0x2E, .addressing = &addressing_modes[Absolute],    .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ROL], .hex = 0x3E, .addressing = &addressing_modes[AbsoluteX],   .cycles = 7, .cycles_vary = false},

  {.instruction = &opcode_types[ROR], .hex = 0x6A, .addressing = &addressing_modes[Accumulator], .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[ROR], .hex = 0x66, .addressing = &addressing_modes[ZeroPage],    .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[ROR], .hex = 0x76, .addressing = &addressing_modes[ZeroPageX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ROR], .hex = 0x6E, .addressing = &addressing_modes[Absolute],    .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[ROR], .hex = 0x7E, .addressing = &addressing_modes[AbsoluteX],   .cycles = 7, .cycles_vary = false},

  {.instruction = &opcode_types[RTI], .hex = 0x40, .addressing = &addressing_modes[Implied],     .cycles = 6, .cycles_vary = false},

  {.instruction = &opcode_types[RTS], .hex = 0x60, .addressing = &addressing_modes[Implied],     .cycles = 6, .cycles_vary = false},

  {.instruction = &opcode_types[SBC], .hex = 0xE9, .addressing = &addressing_modes[Immediate],   .cycles = 2, .cycles_vary = false},
  {.instruction = &opcode_types[SBC], .hex = 0xE5, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[SBC], .hex = 0xF5, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[SBC], .hex = 0xED, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[SBC], .hex = 0xFD, .addressing = &addressing_modes[AbsoluteX],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[SBC], .hex = 0xF9, .addressing = &addressing_modes[AbsoluteY],   .cycles = 4, .cycles_vary = true },
  {.instruction = &opcode_types[SBC], .hex = 0xE1, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[SBC], .hex = 0xF1, .addressing = &addressing_modes[IndirectY],   .cycles = 5, .cycles_vary = true },

  {.instruction = &opcode_types[SEC], .hex = 0x38, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[SED], .hex = 0xF8, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[SEI], .hex = 0x78, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[STA], .hex = 0x85, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[STA], .hex = 0x95, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[STA], .hex = 0x8D, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[STA], .hex = 0x9D, .addressing = &addressing_modes[AbsoluteX],   .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[STA], .hex = 0x99, .addressing = &addressing_modes[AbsoluteY],   .cycles = 5, .cycles_vary = false},
  {.instruction = &opcode_types[STA], .hex = 0x81, .addressing = &addressing_modes[IndirectX],   .cycles = 6, .cycles_vary = false},
  {.instruction = &opcode_types[STA], .hex = 0x91, .addressing = &addressing_modes[IndirectY],   .cycles = 6, .cycles_vary = false},

  {.instruction = &opcode_types[STX], .hex = 0x86, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[STX], .hex = 0x96, .addressing = &addressing_modes[ZeroPageY],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[STX], .hex = 0x8E, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},

  {.instruction = &opcode_types[STY], .hex = 0x84, .addressing = &addressing_modes[ZeroPage],    .cycles = 3, .cycles_vary = false},
  {.instruction = &opcode_types[STY], .hex = 0x94, .addressing = &addressing_modes[ZeroPageX],   .cycles = 4, .cycles_vary = false},
  {.instruction = &opcode_types[STY], .hex = 0x8C, .addressing = &addressing_modes[Absolute],    .cycles = 4, .cycles_vary = false},

  {.instruction = &opcode_types[TAX], .hex = 0xAA, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[TAY], .hex = 0xA8, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[TSX], .hex = 0xBA, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[TXA], .hex = 0x8A, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[TXS], .hex = 0x9A, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false},

  {.instruction = &opcode_types[TYA], .hex = 0x98, .addressing = &addressing_modes[Implied],     .cycles = 2, .cycles_vary = false}
};
