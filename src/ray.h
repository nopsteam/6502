#include <math.h>
#include "raylib.h"

#define E_BLACK  CLITERAL(Color){  0,   0,   0, 255}
#define E_WHITE  CLITERAL(Color){255, 255, 255, 255}
#define E_RED    CLITERAL(Color){136,   0,   0, 255}
#define E_CYAN   CLITERAL(Color){170, 255, 238, 255}
#define E_PINK   CLITERAL(Color){204,  68, 204, 255}
#define E_GREEN  CLITERAL(Color){  0, 204,  85, 255}
#define E_BLUE   CLITERAL(Color){  0,   0, 170, 255}
#define E_YELLOW CLITERAL(Color){238, 238, 119, 255}
#define E_BEIGE  CLITERAL(Color){221, 136,  85, 255}
#define E_BROWN  CLITERAL(Color){102,  68,   0, 255}
#define E_PEACH  CLITERAL(Color){255, 119, 119, 255}
#define E_DRGRAY CLITERAL(Color){ 51,  51,  51, 255}
#define E_MDGRAY CLITERAL(Color){119, 119, 119, 255}
#define E_LIME   CLITERAL(Color){170, 255, 102, 255}
#define E_LTBLUE CLITERAL(Color){  0, 136, 255, 255}
#define E_LTGRAY CLITERAL(Color){187, 187, 187, 255}

extern struct Color colors[16];

int readInput(void);
bool shouldCloseWindow(void);
void initWindow(int scale, int width, int height);
void stopWindow(void);
void drawScreen(int scale, unsigned char display[]);
