/**
  ******************************************************************************
  * @file    main.c
  * @author  Mihai Dicusar
  * @brief   This program reads a BMP file and draws it on the display.
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

#define COMPRESSED_FORMAT	1
#define UNCOMPRESSED_FORMAT 0
#define CORRECT_SIGNATURE	19778

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

		//check for wrong BMP signature
		if (fileHeader.bfType != CORRECT_SIGNATURE)
		{
			ERR_HANDLER(fileHeader.bfType != CORRECT_SIGNATURE,
				"basisChecks: incorrect signature for BMP.");
			continue;
		}

		//check for unsupported bit count
		if (infoHeader.biBitCount != 8)
		{
			ERR_HANDLER(infoHeader.biBitCount != 8,
				"basisChecks: unsupported format: must be 8-bit.");
			continue;
		}

		//check if image width or height is too large, also if exceeds scale factor of 5
		if (infoHeader.biWidth > MAX_ALLOWED_WIDTH || infoHeader.biHeight > MAX_ALLOWED_HEIGHT)
		{
			ERR_HANDLER(infoHeader.biWidth > MAX_ALLOWED_WIDTH || infoHeader.biHeight > MAX_ALLOWED_HEIGHT,
				"basisChecks: image too wide or tall.");
			continue;
		}

		//for uncompressed images
		if(infoHeader.biCompression == UNCOMPRESSED_FORMAT)
		{
			drawUncompressed(infoHeader.biHeight, infoHeader.biWidth, infoHeader.biBitCount, palette);
		}
		//for compressed images
		else if (infoHeader.biCompression == COMPRESSED_FORMAT)
		{
			drawCompressed(infoHeader.biHeight, infoHeader.biWidth, palette);
		}
	}
}

// EOF
