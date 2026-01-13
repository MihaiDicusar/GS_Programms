/**
* @file custom_time.c
* @author Mihai Dicusar
* @date Jan 2026
* @brief This module delays time by given microseconds.
*/

#include <stdint.h>
#include "custom_time.h"

void delay_us(uint32_t us)
{
    uint32_t start = getTimeStamp();
    uint32_t wait_ticks = us * TICKS_PER_US;

    while((getTimeStamp() - start) < wait_ticks)
    {
        //wait
    }
}