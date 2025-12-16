/**
  ******************************************************************************
  * @file    main.c
  * @author  Mihai Dicusar
  * @brief   This program reads inputs from a rotary encoder and displays
  *			 direction, step counter using LEDs, as well as angle and angular
  *			 velocity on the display screen.
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
#include "read_input.h"
#include "output_led.h"
#include "phase.h"
#include "stm32f4xx_hal_def.h"
#include <stdint.h>
#include "timer.h"
#include "custom_time.h"
#include <inttypes.h>
#include <stdio.h>
#include "angle.h"
#include <string.h>
#include "fsm.h"
#include "error_handler.h"
#include "display_output.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	initTimer();

	int last_phase = 0;
	int direction = NO_CHANGE_DIR;
	int initialized = 0;
	int current_phase = 0;
	uint32_t windowStart = 0;
	uint32_t windowEnd = 0;
	int inputA;
	int inputB;

  // Begruessungstext
	display_init();
	windowStart = getTimeStamp(); //t1

	// Test in Endlosschleife
	while(1) {

		int error = 0;
		windowEnd = getTimeStamp(); //t2
		givePinA(&inputA);
		givePinB(&inputB);

		givePhase(&current_phase, inputA, inputB);

		if (!initialized)
		{
			last_phase = current_phase;
			initialized = 1;
		}

		error = giveDirection(&direction, last_phase, current_phase);

		updateCounter(direction);
		updatePhaseCounter(direction);
		update_LED_GPIOE(direction);
		update_LED_GPIOD(getCounter()); //or getPhaseCounter() ?

		uint32_t timeDiff = convert_to_ms(windowStart, windowEnd);

		if (timeDiff >= WINDOW_MIN && last_phase != current_phase || timeDiff >= WINDOW_MAX)
		{
			double angle = getAngle();
			double velocity = getVelocity(timeDiff);

			display_angle(angle);
			display_velocity(velocity);
						
			windowStart = windowEnd;
			resetPhaseCounter();	
		}				

		if (error != 0)
		{
			handle_error();
			initialized = 0;
		}
	    last_phase = current_phase;
	}
}

// EOF
