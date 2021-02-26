#include <stdio.h>
#include <stdlib.h>
#include "sdl.h"

void loop(SDL_Renderer *rend) {
  int current_key = SDL_FIRSTEVENT;

  while (current_key != SDL_QUIT) {
    current_key = readInputSdl();
    drawScreenSdl(rend);
  }

  return;
}

int main()
{
  SDL_Window* win = initWindowSdl();
  SDL_Renderer* rend = initRenderSDL(win);

  loop(rend);

  destroySdl(rend, win);
  return 0; 
}
