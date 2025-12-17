/**
* @file button_input.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module is used to check if the S7 is pressed in order to proceed with
*        the reading and drawing of the next file
*/

#include "button_input.h"
#include "stm32f4xx_hal.h"

int waitButton;

void pollUntilButtonPressed()
{
    waitButton = 1;

    while (waitButton)    //while button not pressed
    {
        if (IDR_MASK_PIN_7 != (GPIOF->IDR & IDR_MASK_PIN_7))    //if pressed
        {
            waitButton = 0;
        }
    }
}