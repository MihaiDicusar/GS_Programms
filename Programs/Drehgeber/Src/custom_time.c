#include "timer.h"
#include <stdint.h>

uint32_t convert_to_ms(uint32_t timeStamp1, uint32_t timeStamp2)
{
    uint32_t timelapse = timeStamp2 - timeStamp1;
    timelapse = timelapse / (TICKS_PER_US * 1000);
    return timelapse;
}