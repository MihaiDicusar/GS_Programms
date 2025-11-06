/**
  ******************************************************************************
  * @file    main.c
  * @author  Mihai Dicusar
  * @brief   This program uses a stack with values and RPN functions to manipulate
			 these values, as well as to display the results on the terminal.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "display.h"
#include "scanner.h"
#include "stack.h"
#include "RPN.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "token.h"


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initDisplay();

	// Test in Endlosschleife
	while(1) {
		T_token token = nextToken();
		char pressedButton = token.tok;
		int tokenVal;
		switch (pressedButton)
		{
			case NUMBER:
				tokenVal = token.val;
				push(tokenVal);
			break;

			case PLUS:
				add();
			break;

			case MINUS:
				subtract();
			break;

			case MULT:
				multiply();
			break;

			case DIV:
				divide();
			break;

			case PRT:
				print();
			break;

			case PRT_ALL:
				printAll();
			break;

			case CLEAR:
				clear();
			break;

			case SWAP:
				swap();
			break;

			case DOUBLE:
				duplicate();
			break;
		}	
	}
}

// EOF
