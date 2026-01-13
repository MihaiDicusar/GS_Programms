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