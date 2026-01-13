/**
* @file onewire_functions.h
* @author Mihai Dicusar
* @date Jan 2026
* @brief Header file of onewire_functions module
*/

#ifndef ONEWIRE_FUNCTIONS_H
#define ONEWIRE_FUNCTIONS_H

#include <stdbool.h>
#include <stdint.h>

#define ROM_LENGTH_BYTES        8
#define SCRATCHPAD_LENGTH_BYTES 9
#define READ_ROM_CMD            0x33
#define MATCH_ROM_CMD           0x55
#define CONVERT_T_CMD           0x44
#define READ_SCRATCHPAD_CMD     0xBE
#define SEARCH_ROM_CMD          0xF0

/**
* @brief This function sets PD0 in open-drain mode on high(1)
*        and PD1 in push-pull mode on high(1)
* @return void   
*/
void idle();

/**
* @brief This function recognizes if any sensor is present
*        on the 1-wire bus, as well as resets the communcation
*        state  machine and ensures the bus is idle and ready
*        for new command
* @return true, if a sensor is present, 
*         else false
*/
bool reset();

/**
* @brief This function gives the ROM number of the only sensor
*        present on the 1-wire bus. 
*        Not applicable for multiple sensors
* @param rom - the adress where the ROM of the sensor will be saved
* @return void
*/
void getROM(uint8_t *rom);

/**
* @brief This function measures and gives temperature from the sensor
* @param temp - adress where the temperature will be saved
* @param rom - the ROM of the sensor from where the temperature should
*                be read
* @return EOK if succesful
*         CRC_ERROR if CRC checking failed
*/
int getTemp(float *temp, uint8_t rom[]);

/**
* @brief This function searches for the all the sensors
*        present on the 1-wire bus
* @param rom - adress where ROM of the sensor will be saved
* @return true(1) if succesful
*         false(0) if failed
*/
int search(uint8_t *rom);

#endif