/**
* @file custom_error.c
* @author Mihai Dicusar
* @date Jan 2026
* @brief This module displays errors on screen when encountered
*/

#include "LCD_GUI.h"
#include "lcd.h"
#include "custom_error.h"

void show_error(int error_code)
{
    GUI_clear(RED);

    switch(error_code)
    {
        case NO_PRESENCE_ERR:
            lcdPrintlnS("ERROR: no sensor present");
        break;

        case INVALID_ROM:
            lcdPrintlnS("ERROR: invalid ROM");
        break;

        case CRC_ERROR:
            lcdPrintlnS("ERROR: invalid CRC from scratchpad");
        break;
        
        default:
            lcdPrintlnS("ERROR: unknown error");
    }   
    
    while(1)
    {
        //endless error screen until restart
    }
}