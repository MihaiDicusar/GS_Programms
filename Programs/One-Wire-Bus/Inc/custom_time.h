/**
* @file custom_time.h
* @author Mihai Dicusar
* @date Jan 2026
* @brief Header file of custom_time module
*/

#ifndef CUSTOM_TIME_H
#define CUSTOM_TIME_H

#include "timer.h"

/**
* @brief This function delays time by given microseconds
*             in the parameter.
* @param us - microseconds to delay
* @return void
*/
void delay_us(uint32_t us);

#endif