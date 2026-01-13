/**
* @file display_output.h
* @author Mihai Dicusar
* @date Jan 2026
* @brief Header file of display_output module
*/

#ifndef DISPLAY_OUTPUT_H
#define DISPLAY_OUTPUT_H

#include <stdint.h>

#define DS18B20 0x28
#define DS18S20 0x10
#define START_Y_POS         1
#define START_X_POS_FAMCODE 1
#define START_X_POS_ROM     10
#define START_X_POS_TEMP    30

/**
* @brief This function displays the Family Code of the sensor
*        on the 1-wire bus
* @param rom - the ROM of the sensor
* @param y - the y-position where Family Code will be displayed
* @return void
*/
void displayFamCode(uint8_t *rom, uint16_t y);

/**
* @brief This function displays the ROM of the sensor
*        on the 1-wire bus
* @param rom - the ROM of the sensor
* @param y - the y-position where ROM will be displayed
* @return void
*/
void displayROM(uint8_t *rom, uint16_t y);

/**
* @brief This function displays the temperature of the sensor
*        on the 1-wire bus
* @param temp - the temperature from the sensor
* @param y - the y-position where temperature will be displayed
* @return void
*/
void displayTemp(float temp, uint16_t y);

#endif