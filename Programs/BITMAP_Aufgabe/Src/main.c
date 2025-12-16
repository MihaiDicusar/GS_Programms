/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "LCD_general.h"
#include "errorhandler.h"
#include "headers.h"
#include "input.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "BMP_types.h"
#include "button_input.h"
#include "rgb.h"
#include <stdint.h>
#include <stdio.h>
#include "draw.h"


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

	lcdGotoXY(1, 1);
	lcdPrintReplS("No input detected, please connect!");
	initInput();
	GUI_clear(WHITE);
	lcdGotoXY(1, 1);
	lcdPrintReplS("Press S7 to proceed!");

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	COLOR palette[256];

	while (1)
	{
		pollUntilButtonPressed();

		GUI_clear(WHITE);

		openNextFile();

		readHeaders();
		getFileHeader(&fileHeader);
		getInfoHeader(&infoHeader);

		fillPallete(infoHeader.biClrUsed, infoHeader.biBitCount);
		getPalette(palette);

		if (infoHeader.biWidth > 2400 || infoHeader.biHeight > 1600)
		{
			ERR_HANDLER(infoHeader.biWidth > 2400 || infoHeader.biHeight > 1600, "basisChecks: image too wide or tall.");
			continue;
		}

		//for uncompressed images
		if(infoHeader.biCompression == 0)
		{
			drawUncompressed(infoHeader.biHeight, infoHeader.biWidth, infoHeader.biBitCount, palette);
		}
		//for compressed images
		else if (infoHeader.biCompression == 1)
		{
			drawCompressed(infoHeader.biHeight, infoHeader.biWidth, palette);
		}
	}
}

// EOF
