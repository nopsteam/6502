#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "disassembler.h"

struct State
{
  int key_quit;
  int key_up;
  int key_left;
  int key_right;
  int key_down;
};

struct Point
{
  int x;
  int y;
};

SDL_Window* init_window()
{
  // returns zero on success else non-zero
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }

  return SDL_CreateWindow("6502",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1000, 1000, 0); 
}

struct State event_manager(struct State state) {
  struct State local_state = state;
  SDL_Event event;

  while (SDL_PollEvent(&event)) {

    if (event.type == SDL_QUIT)
      local_state.key_quit = 1;

    if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
          local_state.key_up = 1;
          break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          local_state.key_left = 1;
          break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
          local_state.key_down = 1;
          break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          local_state.key_right = 1;
          break;
        default:
          break;
      }
    }
    if (event.type == SDL_KEYUP)
    {
      switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
          local_state.key_up = 0;
          break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          local_state.key_left = 0;
          break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
          local_state.key_down = 0;
          break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          local_state.key_right = 0;
          break;
        default:
          break;
      }
    }
  }
  return local_state;
}

void loop(SDL_Renderer* rend)
{
  struct State local_state;
  local_state.key_quit = 0;
  local_state.key_up = 0;
  local_state.key_left = 0;
  local_state.key_right = 0;
  local_state.key_down = 0;

  struct Point pixel;
  pixel.x = 500;
  pixel.y = 500;

  while (!local_state.key_quit) {
    // read input save in state
    local_state = event_manager(local_state);

    // speed
    int speed = 300;

    // set render color black
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    // clears the screen
    SDL_RenderClear(rend);

    // move pixel
    if (local_state.key_up)
      pixel.y -= speed / 30;
    if (local_state.key_left)
      pixel.x -= speed / 30;
    if (local_state.key_down)
      pixel.y += speed / 30;
    if (local_state.key_right)
      pixel.x += speed / 30;

    // right boundary
    if (pixel.x + 1 > 1000)
      pixel.x = 1000 - 1;

    // left boundary
    if (pixel.x < 0)
      pixel.x = 0;

    // bottom boundary
    if (pixel.y + 1 > 1000)
      pixel.y = 1000 - 1;

    // upper boundary
    if (pixel.y < 0)
      pixel.y = 0;

    // set render color red
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    // render four pixels
    SDL_RenderDrawPoint(rend, pixel.x, pixel.y);
    SDL_RenderDrawPoint(rend, pixel.x+1, pixel.y+1);
    SDL_RenderDrawPoint(rend, pixel.x, pixel.y+1);
    SDL_RenderDrawPoint(rend, pixel.x+1, pixel.y);

    // triggers the double buffers for multiple rendering
    SDL_RenderPresent(rend);

    // calculates to 60 fps
    SDL_Delay(1000 / 60);
  }

  return;
}

int main()
{
  LoadBinary("resources/dump.bin");

  SDL_Window* win = init_window();
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

  loop(rend);

  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win); 

  return 0; 
}
