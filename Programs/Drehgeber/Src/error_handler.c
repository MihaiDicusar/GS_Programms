/**
* @file error_handler.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module is used to handle errors
*/

#include "error_handler.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "output_led.h"
#include "read_input.h"
#include "angle.h"
#include "display_output.h"

void handle_error()
{
    int still_error = 1;
    turn_on_LED_GPIOE(D21);
    GUI_clear(RED);
    lcdGotoXY(1, 1);
    lcdPrintlnS("ERROR!");
    lcdPrintlnS("PRESS S6 TO RESET!");
    while (still_error)
    {
        if (check_if_s6_pressed())
        {
            still_error = 0;
            turn_off_LED_GPIOE(D21);
            GUI_clear(WHITE);
            resetCounter();
            display_init();
        }
    }
}