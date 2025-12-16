#include "BMP_types.h"
#include "LCD_general.h"

#define MAX_HEIGHT  320
#define MAX_WIDTH   480

void drawUncompressed(LONG biHeight, LONG biWidth, WORD biBitCount, COLOR *palette);
void drawCompressed(LONG biHeight, LONG biWidth, COLOR *palette);