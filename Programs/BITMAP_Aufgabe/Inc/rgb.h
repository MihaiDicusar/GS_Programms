#include "BMP_types.h"
#include "LCD_general.h"

#define RED_BITS        3
#define GREEN_BITS      2
#define BLUE_BITS       3
#define RED_SHIFT       11
#define GREEN_SHIFT     5
#define BLUE_SHIFT      0

static int readRGB();
int fillPallete(DWORD paletteCount, WORD paletteBitCount); //1.infoHeader.biClrUsed, 2.infoHeader.biBitCount
uint16_t combineRGB(RGBQUAD quad);
int getPalette(COLOR *palette);