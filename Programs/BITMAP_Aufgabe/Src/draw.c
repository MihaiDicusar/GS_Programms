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

void drawUncompressed(LONG biHeight, LONG biWidth, WORD biBitCount, COLOR *palette)
{
    int rowSize = (((biWidth * biBitCount) + 31) / 32) * 4; //padding stuff
	uint8_t rowBuf[rowSize];

	height = (biHeight < MAX_HEIGHT) ? biHeight : MAX_HEIGHT;
    width = (biWidth < MAX_WIDTH) ? biWidth : MAX_WIDTH;

	//allocate buffer
	lineBuf = (COLOR*) malloc(width * sizeof(COLOR));

	//handle failure
    if (lineBuf == NULL) { return; }

	for (int y = 0; y < height; y++)
	{
		COMread((char *) rowBuf, 1, rowSize);
        if (y < height)
        {
            for (int x = 0; x < width; x++)
		    {
                pxIndex = rowBuf[x];
			    lineBuf[x] = palette[pxIndex];
            }
			crd.x = 0;
			crd.y = height - 1 - y;
			GUI_WriteLine(crd, width, lineBuf);
        }   
	}
	free(lineBuf);
}

void drawCompressed(LONG biHeight, LONG biWidth, COLOR *palette)
{
    height = (biHeight < MAX_HEIGHT) ? biHeight : MAX_HEIGHT;
    width = (biWidth < MAX_WIDTH) ? biWidth : MAX_WIDTH;
	endOfBitMap = false;
	int x = 0;
	int y = 0;

	//allocate buffer
	lineBuf = (COLOR*) malloc(width * sizeof(COLOR));
	//handle failure
    if (lineBuf == NULL) { return; }

	while(!endOfBitMap)
	{
		COMread((char *) &count, 1, 1);
		COMread((char *) &value, 1, 1);

		//normal run, aka if first byte(count) is not 0
		if(count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				if (x < width && y < height)
				{
					lineBuf[x] = palette[value];
				}
				x++;
			}
		}
		else 	//if first byte(count) is 0
		{
    		switch (value) 
			{
				case 0:		//end of line reached
				{
					if (y < height)
					{
						crd.x = 0;
						crd.y = height - 1 - y;
						GUI_WriteLine(crd, width, lineBuf);
					}
					x = 0;
					y++;
					break;
				}

				case 1:		//end of bitmap
				{
					if (y < height)
					{
						crd.x = 0;
						crd.y = height - 1 - y;
						GUI_WriteLine(crd, width, lineBuf);
					}
					endOfBitMap = true;		//end of bitmap reached, thus image is fully drawn
					break;
				}

				case 2:		//delta, aka offsets of the next pixel from current
				{
					COMread((char *) &deltaX, 1, 1);
					COMread((char *) &deltaY, 1, 1);

					x += deltaX;
					y += deltaY;
					break;
				}
				default:	//absolute mode, aka if first byte is 0 and second one is between 0x03 and 0xFF
				{
					for(int i = 0; i < value; i++)
					{
						COMread((char *) &pxIndex, 1, 1);

                        if (y < height && x < width)
                        {
							lineBuf[x] = palette[pxIndex];
                        }
						x++;
					}
					if(value & 1)
					{
						COMread((char *) &pad, 1, 1); //padding stuff
					}
					break;
				}
			}
		}
	}

	free(lineBuf);
}