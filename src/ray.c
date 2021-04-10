#include "ray.h"

Color colors[16] = {
  E_BLACK, E_WHITE, E_RED  , E_CYAN  , E_PINK  , E_GREEN, E_BLUE  , E_YELLOW,
  E_BEIGE, E_BROWN, E_PEACH, E_DRGRAY, E_MDGRAY, E_LIME , E_LTBLUE, E_LTGRAY
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
  return CloseWindow();
}

void drawScreen(int scale, unsigned char display[]) {
  BeginDrawing();
  ClearBackground(E_BLACK);
  for (int i = 0; i <= 1023; i++) {
    float y = floor((float)i / 32);
    float x = i % 32;
    Color color = colors[display[i] & 0x0F];
    DrawRectangle(x * scale, y * scale, scale, scale, color);
  }
  DrawText(TextFormat("%2i FPS", GetFPS()), 580, 620, 12, E_LTGRAY);
  EndDrawing();
}
