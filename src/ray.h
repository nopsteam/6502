#include <math.h>
#include "raylib.h"

struct RayColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

extern struct RayColor colors[16];

int readInput(void);
bool shouldCloseWindow(void);
void initWindow(int scale, int width, int height);
void stopWindow(void);
void drawScreen(int scale, unsigned char display[]);
