/**
* @file rgb.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of rgb module
*/

#ifndef RGB_H
#define RGB_H

#include "BMP_types.h"
#include "LCD_general.h"

#define RED_BITS        3
#define GREEN_BITS      2
#define BLUE_BITS       3
#define RED_SHIFT       11
#define GREEN_SHIFT     5
#define BLUE_SHIFT      0

/**
* @brief This method reads the RGB values for 8 bit format
* @return NOK if error encountered
*         EOK if successful
*/
static int readRGB();

/**
* @brief This method reads the RGB values of the file and
*        fills the "palette" Array with this values
* @param paletteCount - in case if it's 0, then converted back to 256 colors
* @param paletteBitCount - bit count of the palette
* @return NOK if paletteCount has invalid values
*         EOK if successful
*/
int fillPallete(DWORD paletteCount, WORD paletteBitCount); //1.infoHeader.biClrUsed, 2.infoHeader.biBitCount

/**
* @brief This method combines the RGB values into one value
* @param quad - the RGB values
* @return the combined color as COLOR
*/
COLOR combineRGB(RGBQUAD quad);

/**
* @brief This method returns the palette
* @return EOK if successful
*/
int getPalette(COLOR *palette);

#endif