/**
* @file gpiod_manip.h
* @author Mihai Dicusar
* @date Jan 2026
* @brief Header file of gpiod_manip module
*/

#ifndef GPIOD_MANIP_H
#define GPIOD_MANIP_H

#include <stdint.h>

#define PD1_PIN	1
#define PD0_PIN 0

/**
* @brief This function initializes PD1 by putting it
*        into push pull mode on high
* @return void
*/
void pd1_init();

/**
* @brief This function initializes PD0 by putting it
*        into open drain mode on high
* @return void
*/
void pd0_init();

/**
* @brief This function puts PD0 into open drain mode
*        on low
* @return void
*/
void pd0_low();

/**
* @brief This function puts PD0 into open drain mode
*        back to high
* @return void
*/
void pd0_high();

/**
* @brief This function gives the read bit from PD0
* @return bit
*/
uint8_t read_pd0();

/**
* @brief This function puts PD0 into push pull mode
*        on high
* @return void
*/
void pd0_high_strong();

#endif