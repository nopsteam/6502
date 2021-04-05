#include "cpu.h"

int hexToDecimalMode(unsigned char hex);
void aslOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void bccOpcode(unsigned int address, struct CPU *cpu);
void bcsOpcode(unsigned int address, struct CPU *cpu);
void beqOpcode(unsigned int address, struct CPU *cpu);
void bitOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void bmiOpcode(unsigned int address, struct CPU *cpu);
void bneOpcode(unsigned int address, struct CPU *cpu);
void bplOpcode(unsigned int address, struct CPU *cpu);
void bvcOpcode(unsigned int address, struct CPU *cpu);
void bvsOpcode(unsigned int address, struct CPU *cpu);
void cpyOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void inxOpcode(unsigned int address, struct CPU *cpu);
void inyOpcode(unsigned int address, struct CPU *cpu);
void jmpOpcode(unsigned int address, struct CPU *cpu);
void jsrOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void ldaOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void ldxOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void ldyOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void nopOpcode();
void phaOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void rtsOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void staOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void stxOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void styOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
void txaOpcode(unsigned int address, struct CPU *cpu);
void txsOpcode(unsigned int address, struct CPU *cpu);
void tyaOpcode(unsigned int address, struct CPU *cpu, struct BUS *bus);
