#include "sdl.h"

SDL_Window* initWindowSdl()
{
  // returns zero on success else non-zero
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }

  return SDL_CreateWindow("6502",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      32 * SCALE, 32 * SCALE, 0);
}

SDL_Renderer* initRenderSDL(SDL_Window* win) {
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  return SDL_CreateRenderer(win, -1, render_flags);
}

void destroySdl(SDL_Renderer * rend, SDL_Window * win) {
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win); 
}

int readInputSdl() {
  int keydown = SDL_FIRSTEVENT;

  SDL_Event event;

  while (SDL_PollEvent(&event)) {

    if (event.type == SDL_QUIT)
      keydown = SDL_QUIT;

    if (event.type == SDL_KEYDOWN)
      keydown = event.key.keysym.scancode;
  }

  return keydown;
}

void drawPixelSdl(struct PIXEL pixel, SDL_Renderer* rend) {
  SDL_SetRenderDrawColor(rend, pixel.color.r, pixel.color.g, pixel.color.b, pixel.color.a);
  SDL_Rect rect = {pixel.x * SCALE, pixel.y * SCALE, SCALE, SCALE};
  SDL_RenderFillRect(rend, &rect);
}

void drawScreenSdl(SDL_Renderer *rend) {
  SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
  SDL_RenderClear(rend);

  for (int i = 0; i <= 1023; i++) {
    float x = floor((float)i / 32);
    float y = i % 32;
    // TODO: struct COLOR color = palette[display[i] & 0x0F];
    struct COLOR color = palette[i % 16];
    struct PIXEL pixel = {.x = x, .y = y, .color = color};

    drawPixelSdl(pixel, rend);
  }

  SDL_RenderPresent(rend);
}
