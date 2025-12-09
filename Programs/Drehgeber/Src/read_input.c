/**
* @file read_input.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module reads the input from pins IN0(Channel A)
*        and IN1(Channel B), as well as from button S6 for error handler.
*/

#include <stdbool.h>
#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"   
#include "error_handler.h"
#include "read_input.h"

#define IDR_MASK_PIN_0  (0x01U << 0)
#define IDR_MASK_PIN_1  (0x01U << 1)
#define IDR_MASK_PIN_6  (0x01U << 6)

int givePinA(int *result)
{
    *result = IDR_MASK_PIN_0 != (GPIOF->IDR & IDR_MASK_PIN_0);
    return RESULT_OK;
}

int givePinB(int *result)
{
    *result = IDR_MASK_PIN_1 != (GPIOF->IDR & IDR_MASK_PIN_1);
    return RESULT_OK;
}

int check_if_s6_pressed()
{
    int pressed = IDR_MASK_PIN_6 != (GPIOF->IDR & IDR_MASK_PIN_6);
    int not_pressed = IDR_MASK_PIN_6 == (GPIOF->IDR & IDR_MASK_PIN_6);

    if (pressed)
    {
        return S6_PRESSED;
    }
    else 
    {
        return S6_NOT_PRESSED;
    }

}


