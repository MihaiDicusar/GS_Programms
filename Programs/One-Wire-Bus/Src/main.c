/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "delay.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "timer.h"
#include "gpiod_manip.h"
#include "onewire_functions.h"
#include "custom_error.h"
#include <stdint.h>
#include <stdio.h>
#include "display_output.h"
#include "crc.h"

#define NR_OF_SENSORS	4

int main(void) {

	uint8_t roms[NR_OF_SENSORS][ROM_LENGTH_BYTES];
	float temp[NR_OF_SENSORS];
	int error_code = 0;

	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	initTimer();

	//get all sensors' ROM

	//init PD0 and PD1, aka idle		
	idle();
	for(int i = 0; i < NR_OF_SENSORS; i++)
	{
		search(roms[i]);

		if(!checkCRC(ROM_LENGTH_BYTES, roms[i]))
		{
			show_error(INVALID_ROM);
		}

		displayFamCode(roms[i], i);
		displayROM(roms[i], i);
	}
	
	//get temperature and show it
	while(1)
	{
		for(int i = 0; i < NR_OF_SENSORS; i++)
		{
			error_code = getTemp(&temp[i], roms[i]);
			if(error_code != EOK)
			{
				show_error(error_code);
			}
			error_code = 0;

			displayTemp(temp[i], i);
		}
	}
}

// EOF
