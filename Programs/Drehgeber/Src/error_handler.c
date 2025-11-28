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
    lcdPrintlnS("FEHLER AUFGETRETEN!");
    lcdPrintlnS("DRUECKE S6, UM DEN FEHLER ZU LOESCHEN!");
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