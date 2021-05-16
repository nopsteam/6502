#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "cpu.h"
#include <time.h>    

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
    unsigned char input = (unsigned char)readInput();

    if (input > 0) {
      bus->input = input;
      printf("%i", bus->input);
    }

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
  stopWindow();

  return 0;
}
