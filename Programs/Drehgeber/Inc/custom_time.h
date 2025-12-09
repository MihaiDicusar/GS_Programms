/**
* @file custom_time.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of custom_time module
*/

#ifndef CUSTOM_TIME_H
#define CUSTOM_TIME_H

#include <stdint.h>

#define WINDOW_MIN   250
#define WINDOW_MAX   500

/**
* @brief This function calculates the time difference from two timestamps
*        and the result is then converted from ticks into ms
* @param timeStamp1 - first timestamp
* @param timeStamp2 - second timestamp
* @return time difference as uint32_t
*/
uint32_t convert_to_ms(uint32_t timeStamp1, uint32_t timeStamp2);

#endif