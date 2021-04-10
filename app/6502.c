#include <stdio.h>
#include "ray.h"
#include "cpu.h"

const int scale = 20;
const int screenWidth = 32;
const int screenHeight = 32;

int initSimulator (struct CPU * cpu, struct BUS * bus, int initial_address, char * programPath) {
  writeBus(0xFFFC, initial_address & 0xff, bus);
  writeBus(0xFFFD, (initial_address >> 8), bus);
  resetCpu(cpu, bus);
  return writeProgramToBus(programPath, initial_address, bus);
}

void loop(struct CPU * cpu, struct BUS * bus) {
  while (shouldCloseWindow())
  {
    bus->input = (unsigned char)readInput();
    drawScreen(scale, bus->display);
    clockCpu(cpu, bus);
  }
}

int main(int argc, char **argv)
{
  char * programPath = NULL;
  if (argc > 1) {
    programPath = argv[1];
  } else {
    printf("Usage:\n       6502 file...\n");
    return 1;
  }

  struct CPU cpu;
  struct BUS bus = initializeBus();

  if(initSimulator(&cpu, &bus, 0x0600, programPath) != 0) 
    return 1;

  initWindow(scale, screenWidth, screenHeight);
  loop(&cpu, &bus);

  CloseWindow();

  return 0;
}
