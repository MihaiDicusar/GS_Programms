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