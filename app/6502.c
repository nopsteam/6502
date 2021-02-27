#include <stdio.h>
#include "cpu.h"
#include "sdl.h"

void loop(SDL_Renderer *rend, struct CPU * cpu, struct BUS * bus) {
  int current_key = SDL_FIRSTEVENT;

  while (current_key != SDL_QUIT) {
    current_key = readInputSdl();
    bus->input = (unsigned char)current_key;
    drawScreenSdl(rend, bus->display);
    clockCpu(cpu, bus);
  }

  return;
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
  resetCpu(&cpu, &bus);

  writeFileBus(programPath, 0x200, &bus); // TODO: Switch to 0x600 offset
  SDL_Window* win = initWindowSdl();
  SDL_Renderer* rend = initRenderSDL(win);

  loop(rend, &cpu, &bus);

  destroySdl(rend, win);
  return 0;
}
