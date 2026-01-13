#include <stdint.h>
#include "lcd.h"
#include "onewire_functions.h"
#include <stdio.h>
#include <string.h>
#include "display_output.h"

/**
* @file display_output.c
* @author Mihai Dicusar
* @date Jan 2026
* @brief This module displays the family code, the ROM
*        and the temperature of the sensor
*/

void displayFamCode(uint8_t *rom, uint16_t y)
{
    char buf[50];

    switch (rom[0])
    {
        case DS18B20:
            sprintf(buf, "DS18B20");
        break;

        case DS18S20:
            sprintf(buf, "DS18S20");
        break;

        default:
            sprintf(buf, "N/A");
    }

    lcdGotoXY(START_X_POS_FAMCODE, START_Y_POS + y);
    lcdPrintlnS(buf);
}

void displayROM(uint8_t *rom, uint16_t y)
{
    char bufROM[100];
    sprintf(bufROM, "0x");

    for(int i = 0; i < ROM_LENGTH_BYTES; i++)
    {
        char buf[4];
        sprintf(buf, "%02X", rom[i]);
        strcat(bufROM, buf);
    }

    lcdGotoXY(START_X_POS_ROM, START_Y_POS + y);
    lcdPrintlnS(bufROM);
}

void displayTemp(float temp, uint16_t y)
{
    char buf[20];
    sprintf(buf, "%.4f", temp);
    lcdGotoXY(START_X_POS_TEMP, START_Y_POS + y);
    lcdPrintlnS(buf);
}