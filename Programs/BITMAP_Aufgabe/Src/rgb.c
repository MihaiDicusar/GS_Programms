/**
* @file rgb.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module is used to read RGB 
*        values from COMread and to fill the palette
*/

#include "BMP_types.h"
#include "LCD_general.h"
#include "errorhandler.h"
#include "input.h"
#include <stdint.h>
#include "rgb.h"

static RGBQUAD rgbQuad;
static RGBQUAD palette[256];
static uint16_t convertedPalette[256];

static int readRGB()
{
   RETURN_NOK_ON_ERR(1 != COMread((char *) &rgbQuad, sizeof(RGBQUAD), 1),"readRGB: Error during read.");
   return EOK;
}

int fillPallete(DWORD paletteCount, WORD paletteBitCount)
{
   if(paletteCount == 0)
   {
      paletteCount = 1 << paletteBitCount;
   }

   if (paletteCount <= 0 || paletteCount > 256)
   {
      return NOK;
   }

   for(int i = 0; i < paletteCount; i++)
	{
		readRGB();
		palette[i] = rgbQuad;
	}
   for(int i = 0; i < paletteCount; i++)
   {
      convertedPalette[i] = combineRGB(palette[i]);
   }
   return EOK;
}

int getPalette(COLOR *outPalette)
{
   for(int i = 0; i < 256; i++)
   {
      outPalette[i] = convertedPalette[i];
   }
   return EOK;
}

COLOR combineRGB(RGBQUAD quad)
{
   return ((quad.rgbRed >> RED_BITS) << RED_SHIFT) |
          ((quad.rgbGreen >> GREEN_BITS) << GREEN_SHIFT) |
          ((quad.rgbBlue >> BLUE_BITS) << BLUE_SHIFT);
}