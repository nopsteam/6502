#include "ray.h"
#include "raylib.h"

struct RayColor colors[16] = {
  {.r =   0, .g =   0, .b =   0, .a = 255},  //BLACK
  {.r = 255, .g = 255, .b = 255, .a = 255},  //WHITE
  {.r = 136, .g =   0, .b =   0, .a = 255},  //RED
  {.r = 170, .g = 255, .b = 238, .a = 255},  //CYAN
  {.r = 204, .g =  68, .b = 204, .a = 255},  //PINK
  {.r =   0, .g = 204, .b =  85, .a = 255},  //GREEN
  {.r =   0, .g =   0, .b = 170, .a = 255},  //BLUE
  {.r = 238, .g = 238, .b = 119, .a = 255},  //YELLOW
  {.r = 221, .g = 136, .b =  85, .a = 255},  //BEIGE
  {.r = 102, .g =  68, .b =   0, .a = 255},  //BROWN
  {.r = 255, .g = 119, .b = 119, .a = 255},  //PEACH
  {.r =  51, .g =  51, .b =  51, .a = 255},  //DRGRAY
  {.r = 119, .g = 119, .b = 119, .a = 255},  //MDGRAY
  {.r = 170, .g = 255, .b = 102, .a = 255},  //LIME
  {.r =   0, .g = 136, .b = 255, .a = 255},  //LTBLUE
  {.r = 187, .g = 187, .b = 187, .a = 255}   //LTGRAY
};

int readInput(void) {
  return GetCharPressed();
}

bool shouldCloseWindow(void) {
  return !WindowShouldClose(); // Detect window close button or ESC key
}

void initWindow(int scale, int width, int height)
{
  InitWindow(width * scale, height * scale, "6502 Emulator by N0ps");
  SetTargetFPS(0);
}

void stopWindow(void)
{
  CloseWindow();
}

void drawScreen(int scale, unsigned char display[]) {
  BeginDrawing();
  ClearBackground(BLACK);
  for (int i = 0; i <= 1023; i++) {
    float y = floor((float)i / 32);
    float x = i % 32;
    struct RayColor raycolor = colors[display[i] & 0x0F];
    Color color = {.r = raycolor.r, .g = raycolor.g, .b = raycolor.b, .a = raycolor.a };
    DrawRectangle(x * scale, y * scale, scale, scale, color);
  }
  DrawText(TextFormat("%2i FPS", GetFPS()), 580, 620, 12, LIGHTGRAY);
  EndDrawing();
}
