#include "ray.h"

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
