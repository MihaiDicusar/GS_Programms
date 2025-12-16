#include "BMP_types.h"
#include "LCD_general.h"
#include "LCD_GUI.h"
#include <stdbool.h>
#include "MS_basetypes.h"
#include "input.h"
#include "draw.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int height;
int width;
COLOR *lineBuf;
uint8_t pxIndex;
Coordinate crd;
int x;
int y;
bool endOfBitMap;
uint8_t count;
uint8_t value;
uint16_t actualWidth;
uint8_t deltaX;
uint8_t deltaY;
uint8_t pad;	//pad byte
static int rAcc[MAX_WIDTH], gAcc[MAX_WIDTH], bAcc[MAX_WIDTH], countAcc[MAX_WIDTH];

static inline void unpackRGB565(uint16_t c, int *r, int *g, int *b) {
    int rawR = (c >> 11) & 0x1F;  // 5 bits
    int rawG = (c >> 5)  & 0x3F;  // 6 bits
    int rawB =  c        & 0x1F;  // 5 bits

    *r = (rawR * 255) / 31;
    *g = (rawG * 255) / 63;
    *b = (rawB * 255) / 31;
}

static inline uint16_t packRGB565(int r, int g, int b) {
    int rawR = (r * 31) / 255;
    int rawG = (g * 63) / 255;
    int rawB = (b * 31) / 255;

    return (uint16_t)((rawR << 11) | (rawG << 5) | rawB);
}

void drawUncompressed(LONG biHeight, LONG biWidth, WORD biBitCount, COLOR *palette)
{
    int rowSize = (((biWidth * biBitCount) + 31) / 32) * 4; //padding stuff
	uint8_t rowBuf[rowSize];

	int scaleX = (biWidth + MAX_WIDTH - 1) / MAX_WIDTH;
	int scaleY = (biHeight + MAX_HEIGHT - 1) / MAX_HEIGHT;
	int scaleFactor = (scaleX > scaleY) ? scaleX : scaleY;

	int outWidth = biWidth / scaleFactor;
	int outHeight = biHeight / scaleFactor;

	//allocate buffer
	lineBuf = (COLOR*) malloc(outWidth * sizeof(COLOR));

	//handle failure
    if (lineBuf == NULL) { return; }

	for (int y = 0; y < biHeight; y++)
	{
		COMread((char *) rowBuf, 1, rowSize);
        if (y % scaleFactor == 0)
		{
			int outRow = y / scaleFactor;
			if (outRow >= outHeight) break;

            for (int x = 0; x < biWidth; x++)
		    {
				if(x % scaleFactor == 0)
				{
					int outCol = x / scaleFactor;
					if (outCol < outWidth)
					{
						pxIndex = rowBuf[x];
			    		lineBuf[outCol] = palette[pxIndex];
					}
				}
            }
			crd.x = 0;
			crd.y = outHeight - 1 - outRow;
			GUI_WriteLine(crd, outWidth, lineBuf);
        }   
	}
	free(lineBuf);
}

void drawCompressed(LONG biHeight, LONG biWidth, COLOR *palette)
{
    // Compute dynamic scaling
    int scaleX = (biWidth  + MAX_WIDTH  - 1) / MAX_WIDTH;
    int scaleY = (biHeight + MAX_HEIGHT - 1) / MAX_HEIGHT;
    int scaleFactor = (scaleX > scaleY) ? scaleX : scaleY;
    if (scaleFactor < 1) scaleFactor = 1;
    if (scaleFactor > 5) scaleFactor = 5;   // clamp to assignment requirement

    int outWidth  = biWidth  / scaleFactor;
    int outHeight = biHeight / scaleFactor;
    if (outWidth  < 1) outWidth  = 1;
    if (outHeight < 1) outHeight = 1;
    if (outWidth  > MAX_WIDTH)  outWidth  = MAX_WIDTH;
    if (outHeight > MAX_HEIGHT) outHeight = MAX_HEIGHT;

    COLOR *lineBuf = (COLOR*) malloc(outWidth * sizeof(COLOR));
    if (!lineBuf) return;

    // clear accumulators
    for (int i = 0; i < outWidth; i++) {
        rAcc[i] = gAcc[i] = bAcc[i] = countAcc[i] = 0;
    }

    int x = 0, y = 0;
    bool endOfBitmap = false;

    while (!endOfBitmap) {
        uint8_t count, value;
        COMread((char*)&count, 1, 1);
        COMread((char*)&value, 1, 1);

        if (count > 0) {
            // Encoded run
            for (int i = 0; i < count; i++) {
                if (x < biWidth && y < biHeight) {
                    int oc = x / scaleFactor;
                    if (oc < outWidth) {
                        int r,g,b;
                        unpackRGB565(palette[value], &r,&g,&b);
                        rAcc[oc]     += r;
                        gAcc[oc]     += g;
                        bAcc[oc]     += b;
                        countAcc[oc] += 1;
                    }
                }
                x++;
            }
        } else {
            switch (value) {
                case 0: { // End of line
                    y++;
                    x = 0;

                    if (y > 0 && (y % scaleFactor) == 0) {
                        int outRow = (y / scaleFactor) - 1;
                        if (outRow >= 0 && outRow < outHeight) {
                            for (int oc = 0; oc < outWidth; oc++) {
                                if (countAcc[oc] > 0) {
                                    int r = rAcc[oc] / countAcc[oc];
                                    int g = gAcc[oc] / countAcc[oc];
                                    int b = bAcc[oc] / countAcc[oc];
                                    lineBuf[oc] = packRGB565(r,g,b);
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

                case 1: { // End of bitmap
                    int outRow = y / scaleFactor;
                    if (outRow >= 0 && outRow < outHeight) {
                        for (int oc = 0; oc < outWidth; oc++) {
                            if (countAcc[oc] > 0) {
                                int r = rAcc[oc] / countAcc[oc];
                                int g = gAcc[oc] / countAcc[oc];
                                int b = bAcc[oc] / countAcc[oc];
                                lineBuf[oc] = packRGB565(r,g,b);
                            }
                        }
                        crd.x = 0;
                        crd.y = outHeight - 1 - outRow;
                        GUI_WriteLine(crd, outWidth, lineBuf);
                    }
                    endOfBitmap = true;
                } break;

                case 2: { // Delta
                    uint8_t dx, dy;
                    COMread((char*)&dx, 1, 1);
                    COMread((char*)&dy, 1, 1);
                    x += dx;
                    y += dy;
                } break;

                default: { // Absolute mode
                    for (int i = 0; i < value; i++) {
                        uint8_t pxIndex;
                        COMread((char*)&pxIndex, 1, 1);
                        if (x < biWidth && y < biHeight) {
                            int oc = x / scaleFactor;
                            if (oc < outWidth) {
                                int r,g,b;
                                unpackRGB565(palette[pxIndex], &r,&g,&b);
                                rAcc[oc]     += r;
                                gAcc[oc]     += g;
                                bAcc[oc]     += b;
                                countAcc[oc] += 1;
                            }
                        }
                        x++;
                    }
                    if (value & 1) {
                        uint8_t pad;
                        COMread((char*)&pad, 1, 1);
                    }
                } break;
            }
        }
    }

    free(lineBuf);
}