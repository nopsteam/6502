#include <math.h>
#include <SDL2/SDL.h>

#define SCALE 20

struct COLOR
{
  int r;
  int g;
  int b;
  int a;
};

struct PIXEL
{
  int x;
  int y;
  struct COLOR color;
};

struct COLOR palette[16] = {
  {.r =   0, .g =   0, .b =   0, .a = 255}, //"000000"
  {.r = 255, .g = 255, .b = 255, .a = 255}, //"ffffff"
  {.r = 136, .g =   0, .b =   0, .a = 255}, //"880000"
  {.r = 170, .g = 255, .b = 238, .a = 255}, //"aaffee"
  {.r = 204, .g =  68, .b = 204, .a = 255}, //"cc44cc"
  {.r =   0, .g = 204, .b =  85, .a = 255}, //"00cc55"
  {.r =   0, .g =   0, .b = 170, .a = 255}, //"0000aa"
  {.r = 238, .g = 238, .b = 119, .a = 255}, //"eeee77"
  {.r = 221, .g = 136, .b =  85, .a = 255}, //"dd8855"
  {.r = 102, .g =  68, .b =   0, .a = 255}, //"664400"
  {.r = 255, .g = 119, .b = 119, .a = 255}, //"ff7777"
  {.r =  51, .g =  51, .b =  51, .a = 255}, //"333333"
  {.r = 119, .g = 119, .b = 119, .a = 255}, //"777777"
  {.r = 170, .g = 255, .b = 102, .a = 255}, //"aaff66"
  {.r =   0, .g = 136, .b = 255, .a = 255}, //"0088ff"
  {.r = 187, .g = 187, .b = 187, .a = 255}  //"bbbbbb"
};

SDL_Window* initWindowSdl();
SDL_Renderer* initRenderSDL(SDL_Window* win);
void destroySdl(SDL_Renderer * rend, SDL_Window * win);
int readInputSdl();
void drawScreenSdl(SDL_Renderer *rend);
