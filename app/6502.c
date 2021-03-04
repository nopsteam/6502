#include <stdio.h>
#include "cpu.h"
#include "sdl.h"

void initSimulator (struct CPU * cpu, struct BUS * bus, int initial_address, char * programPath) {
  writeBus(0xFFFC, initial_address & 0xff, bus);
  writeBus(0xFFFD, (initial_address >> 8), bus);
  resetCpu(cpu, bus);
  writeProgramToBus(programPath, initial_address, bus);
}

void loop(SDL_Renderer *rend, struct CPU * cpu, struct BUS * bus) {
  int current_key = SDL_FIRSTEVENT;

  while (current_key != SDL_QUIT) {
    current_key = readInputSdl();
    bus->input = (unsigned char)current_key;
    drawScreenSdl(rend, bus->display);
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
  initSimulator(&cpu, &bus, 0x0200, programPath);

  SDL_Window* win = initWindowSdl();
  SDL_Renderer* rend = initRenderSDL(win);

  loop(rend, &cpu, &bus);

  destroySdl(rend, win);

  return 0;
}
