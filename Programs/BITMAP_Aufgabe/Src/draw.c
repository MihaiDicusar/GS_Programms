/**
* @file draw.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module is used to draw uncompressed and compressed images
*        on the display
*/

#include "BMP_types.h"
#include "LCD_general.h"
#include "LCD_GUI.h"
#include <stdbool.h>
#include "MS_basetypes.h"
#include "input.h"
#include "draw.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

COLOR *lineBuf;
uint8_t pxIndex;
Coordinate crd;
int x;
int y;
bool endOfBitMap;
uint8_t count;
uint8_t value;
uint8_t pad;	//pad byte
int scaleX;
int scaleY;
int scaleFactor;
int outWidth;
int outHeight;

//accumulators for averaging of pixels
static int rAcc[MAX_WIDTH], gAcc[MAX_WIDTH], bAcc[MAX_WIDTH], countAcc[MAX_WIDTH];

static void unpackRGB(COLOR c, int *r, int *g, int *b) {
    int rawR = (c >> 11) & 0x1F;  // 5 bits
    int rawG = (c >> 5)  & 0x3F;  // 6 bits
    int rawB =  c        & 0x1F;  // 5 bits

    *r = (rawR * 255) / 31;
    *g = (rawG * 255) / 63;
    *b = (rawB * 255) / 31;
}

static COLOR packRGB(int r, int g, int b) {
    int rawR = (r * 31) / 255;
    int rawG = (g * 63) / 255;
    int rawB = (b * 31) / 255;

    return (COLOR)((rawR << 11) | (rawG << 5) | rawB);
}

void drawUncompressed(LONG biHeight, LONG biWidth, WORD biBitCount, COLOR *palette)
{
    int rowSize = (((biWidth * biBitCount) + 31) / 32) * 4; //padding for correct alignment
	uint8_t rowBuf[rowSize];

	int scaleX = (biWidth + MAX_WIDTH - 1) / MAX_WIDTH;
	int scaleY = (biHeight + MAX_HEIGHT - 1) / MAX_HEIGHT;
	int scaleFactor = (scaleX > scaleY) ? scaleX : scaleY;  //which scale will be applied for both axes

    //what width or height will be drawn
	int outWidth = biWidth / scaleFactor;
	int outHeight = biHeight / scaleFactor;
    if (outWidth > MAX_WIDTH) outWidth = MAX_WIDTH;
    if (outHeight > MAX_HEIGHT) outHeight = MAX_HEIGHT;

	//allocate buffer
	lineBuf = (COLOR*) malloc(outWidth * sizeof(COLOR));

	//handle failure
    if (lineBuf == NULL) { return; }

    // clear accumulators
    for(int i = 0; i < outWidth; i++)
    {
        rAcc[i] = gAcc[i] = bAcc[i] = countAcc[i] = 0;
    }

    for(int y = 0; y < biHeight; y++)
    {
        COMread((char *) rowBuf, 1, rowSize);
        for (int x = 0; x < biWidth; x++)
        {
            int outCol = x / scaleFactor;
            if(outCol < outWidth)
            {
                pxIndex = rowBuf[x];
                int r, g, b;
                unpackRGB(palette[pxIndex], &r, &g, &b);
                rAcc[outCol] += r;
                gAcc[outCol] += g;
                bAcc[outCol] += b;
                countAcc[outCol] += 1;
            }
        }

        if ((y + 1) % scaleFactor == 0)
        {
            int outRow = (y + 1) / scaleFactor - 1;
            if(outRow >= outHeight) { break; }

            for(int outCol = 0; outCol < outWidth; outCol++)
            {
                if(countAcc[outCol] > 0)
                {
                    //do averaging of the colors and pack as one color
                    int r = rAcc[outCol] / countAcc[outCol];
                    int g = gAcc[outCol] / countAcc[outCol];
                    int b = bAcc[outCol] / countAcc[outCol];
                    lineBuf[outCol] = packRGB(r, g, b);
                }
            }

            crd.x = 0;
            crd.y = outHeight - 1 - outRow;
            GUI_WriteLine(crd, outWidth, lineBuf);

            // clear accumulators
            for(int i = 0; i < outWidth; i++)
            {
                rAcc[i] = gAcc[i] = bAcc[i] = countAcc[i] = 0;
            }
        }
    }
	
	free(lineBuf);
}

void drawCompressed(LONG biHeight, LONG biWidth, COLOR *palette)
{
    scaleX = (biWidth  + MAX_WIDTH  - 1) / MAX_WIDTH;
    scaleY = (biHeight + MAX_HEIGHT - 1) / MAX_HEIGHT;
    scaleFactor = (scaleX > scaleY) ? scaleX : scaleY;  //which scale will be applied for both axes
    if (scaleFactor < 1) scaleFactor = 1;
    if (scaleFactor > 5) scaleFactor = 5; 

    //what width or height will be drawn
    outWidth  = biWidth  / scaleFactor;     
    outHeight = biHeight / scaleFactor;

    if (outWidth  < 1) outWidth  = 1;
    if (outHeight < 1) outHeight = 1;
    if (outWidth  > MAX_WIDTH)  outWidth  = MAX_WIDTH;
    if (outHeight > MAX_HEIGHT) outHeight = MAX_HEIGHT;

    lineBuf = (COLOR*) malloc(outWidth * sizeof(COLOR));
    if (!lineBuf) return;

    // clear accumulators
    for (int i = 0; i < outWidth; i++) {
        rAcc[i] = gAcc[i] = bAcc[i] = countAcc[i] = 0;
    }

    x = 0;
    y = 0;
    bool endOfBitmap = false;

    while (!endOfBitmap) {
        COMread((char*)&count, 1, 1);
        COMread((char*)&value, 1, 1);

        if (count > 0) {    //if first byte(count) is 0
            // Encoded run
            for (int i = 0; i < count; i++) {
                if (x < biWidth && y < biHeight) {
                    int outCol = x / scaleFactor; 
                    if (outCol < outWidth) {
                        int r,g,b;
                        unpackRGB(palette[value], &r,&g,&b);
                        rAcc[outCol]     += r;
                        gAcc[outCol]     += g;
                        bAcc[outCol]     += b;
                        countAcc[outCol] += 1;
                    }
                }
                x++;
            }
        } else {
            switch (value) {
                case 0: { // End of line, value is 0, thus draw the line
                    y++;
                    x = 0;

                    if (y > 0 && (y % scaleFactor) == 0) {
                        int outRow = (y / scaleFactor) - 1;
                        if (outRow >= 0 && outRow < outHeight) {
                            for (int outCol = 0; outCol < outWidth; outCol++) {
                                if (countAcc[outCol] > 0) {
                                    //do averaging of the colors and pack as one color
                                    int r = rAcc[outCol] / countAcc[outCol];
                                    int g = gAcc[outCol] / countAcc[outCol];
                                    int b = bAcc[outCol] / countAcc[outCol];
                                    lineBuf[outCol] = packRGB(r,g,b);
                                }
                            }
                            crd.x = 0;
                            crd.y = outHeight - 1 - outRow;
                            GUI_WriteLine(crd, outWidth, lineBuf);

                            // reset accumulators
                            for (int i = 0; i < outWidth; i++) {
                                rAcc[i] = gAcc[i] = bAcc[i] = countAcc[i] = 0;
                            }
                        }
                    }
                } break;

                case 1: { // End of bitmap, last row of image will be drawn
                    int outRow = y / scaleFactor;
                    if (outRow >= 0 && outRow < outHeight) {
                        for (int outCol = 0; outCol < outWidth; outCol++) {
                            if (countAcc[outCol] > 0) {
                                int r = rAcc[outCol] / countAcc[outCol];
                                int g = gAcc[outCol] / countAcc[outCol];
                                int b = bAcc[outCol] / countAcc[outCol];
                                lineBuf[outCol] = packRGB(r,g,b);
                            }
                        }
                        crd.x = 0;
                        crd.y = outHeight - 1 - outRow;
                        GUI_WriteLine(crd, outWidth, lineBuf);
                    }
                    endOfBitmap = true;
                } break;

                case 2: { // Delta, offset of next pixel from current pixel
                    uint8_t deltaX;
                    uint8_t deltaY;

                    COMread((char*)&deltaX, 1, 1);
                    COMread((char*)&deltaY, 1, 1);
                    x += deltaX;
                    y += deltaY;
                } break;

                default: { // Absolute mode, when count is 0 and value bigger than 3
                    for (int i = 0; i < value; i++) {
                        COMread((char*)&pxIndex, 1, 1);
                        if (x < biWidth && y < biHeight) {
                            int outCol = x / scaleFactor;
                            if (outCol < outWidth) {
                                int r,g,b;
                                unpackRGB(palette[pxIndex], &r,&g,&b);
                                rAcc[outCol]     += r;
                                gAcc[outCol]     += g;
                                bAcc[outCol]     += b;
                                countAcc[outCol] += 1;
                            }
                        }
                        x++;
                    }
                    if (value & 1) {
                        COMread((char*)&pad, 1, 1); //padding for correct alignment
                    }
                } break;
            }
        }
    }

    free(lineBuf);
}