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

  // Begruessungstext
	display_init();
	
	// Test in Endlosschleife
	while(1) {

		int error = 0;
		
		int inputA;
		int inputB;

		givePinA(&inputA);
		givePinB(&inputB);

		givePhase(&current_phase, inputA, inputB);

		//if first run
		if (!initialized)
		{
			last_phase = current_phase;
			direction = NO_CHANGE_DIR;
			initialized = 1;
		}

		error = giveDirection(&direction, last_phase, current_phase);

		last_phase = current_phase;

		updateCounter(direction);
		updatePhaseCounter(direction);
		update_LED_GPIOE(direction);
		update_LED_GPIOD(getCounter());

		if (windowStart == 0)
		{
			windowStart = getTimeStamp();
		}

		if (windowStart != 0)
		{
			windowEnd = getTimeStamp();
			uint32_t timeDiff = convert_to_ms(windowStart, windowEnd);

			if (timeDiff >= WINDOW_MIN)
			{
				double angle = getAngle();
				double velocity = getVelocity(timeDiff);

				display_angle(angle);
				display_velocity(velocity);

				if ((timeDiff >= WINDOW_MIN && direction != NO_CHANGE_DIR) ||
					timeDiff >= WINDOW_MAX)
				{
					windowStart = 0;
					resetPhaseCounter();
				}
			}
		}

		if (error != 0)
		{
			handle_error();
			initialized = 0;
		}
	}
}

// EOF
