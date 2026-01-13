#include <stdint.h>
#include "gpiod_manip.h"
#include "custom_time.h"
#include "read_write.h"

void write_bit(uint8_t bit)
{
    if(bit)     //write 1
    {
        pd0_low();
        delay_us(6);
        pd0_high();
        delay_us(64);
    }
    else {      //write 0
        pd0_low();
        delay_us(60);
        pd0_high();
        delay_us(10);
    }
}

void write_byte(uint8_t byte)
{
    for(int i = 0; i < BYTE_LENGTH; i++)
    {
        write_bit(byte & 0x01);     //send LSB
        byte >>= 1;     //shift to next bit
    }
}

uint8_t read_bit()
{
    uint8_t bit;

    pd0_low();
    delay_us(6);
    pd0_high();
    delay_us(9);
    bit = read_pd0();
    delay_us(55);

    return bit;
}

uint8_t read_byte()
{
    uint8_t value = 0;

    for(int i = 0; i < BYTE_LENGTH; i++)
    {
        uint8_t bit = read_bit();
        value >>= 1;
        if(bit)
        {
            value |= 0x80;      //convert from LSB to MSB
        }
    }
    return value;
}