/**
* @file draw.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of draw module
*/

#ifndef DRAW_H
#define DRAW_H

#include "BMP_types.h"
#include "LCD_general.h"

#define MAX_HEIGHT          320
#define MAX_WIDTH           480
#define MAX_ALLOWED_HEIGHT  2400
#define MAX_ALLOWED_WIDTH   1600 

/**
* @brief This method draws the uncompressed format image on the display, downscaled if necessary
* @param biHeight - height of the image from file header
* @param biWidth - width of the image from file header
* @param biBitCount - bit count of the file, needed for padding
* @param palette - the palette with the colors needed for drawing
* @return void
*/
void drawUncompressed(LONG biHeight, LONG biWidth, WORD biBitCount, COLOR *palette);

/**
* @brief This method draws the compressed format image on the display, downscaled if necessary
* @param biHeight - height of the image from file header
* @param biWidth - width of the image from file header
* @param palette - the palette with the colors needed for drawing
* @return void
*/
void drawCompressed(LONG biHeight, LONG biWidth, COLOR *palette);

/**
* @brief This method is used to unpack RGB values from one combined value
* @param c - color to unpack
* @return void
*/
static void unpackRGB(COLOR c, int *r, int *g, int *b);

/**
* @brief This method is used to pack RGB values into one combined value
* @param r, g, b - RGB values to pack into one color
* @return the packed color as COLOR
*/
static COLOR packRGB(int r, int g, int b);

#endif