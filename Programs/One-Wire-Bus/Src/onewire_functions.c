#include "crc.h"
#include "delay.h"
#include "gpiod_manip.h"
#include "onewire_functions.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "custom_time.h"
#include "read_write.h"
#include <stdint.h>
#include "custom_error.h"

static uint8_t rom_nr[ROM_LENGTH_BYTES];	//current ROM
static int last_discrepancy = 0;	//at what position there was a conflict
static int last_sensor_flag = 0;	
static int last_family_discrepancy = 0; //for family of the sensor, for example 0x10 or 0x28

void idle()
{
	pd1_init();		//PD1 = 1
	pd0_init();		//PD0 = 1
}

bool reset()
{
	bool present = false;

	pd0_low();	//PD0 = 0
	delay_us(480);
	pd0_high();  //PD0 = 1
	delay_us(80);	//70 us makes 1st run with no presence...

	//if a sensor is present
	if((GPIOD->IDR & (1 << PD0_PIN)) == 0)
	{
		present = true;
	}

    delay_us(410);

	return present;
}

//when only one sensor is present
void getROM(uint8_t *rom)
{
    write_byte(READ_ROM_CMD);
    for(int i = 0; i < ROM_LENGTH_BYTES; i++)
    {
        rom[i] = read_byte();
    }
}

int getTemp(float *temp, uint8_t rom[])
{
	uint8_t scratchpad[SCRATCHPAD_LENGTH_BYTES];

	reset();
	write_byte(MATCH_ROM_CMD);		//0x55
	for(int i = 0; i < ROM_LENGTH_BYTES; i++)
	{
		write_byte(rom[i]);
	}

	write_byte(CONVERT_T_CMD);		//0x44
	pd0_high_strong();		//otherwise current too weak, thus no temperature reading
	delay(750);
	pd0_init();		//safety reason, back to open drain after strong push pull

	reset();
	write_byte(MATCH_ROM_CMD);		//0x55
	for(int i = 0; i < ROM_LENGTH_BYTES; i++)
	{
		write_byte(rom[i]);
	}

	write_byte(READ_SCRATCHPAD_CMD);		//0xBE

	for(int i = 0; i < SCRATCHPAD_LENGTH_BYTES; i++)
	{
		scratchpad[i] = read_byte();
	}

	if(!checkCRC(SCRATCHPAD_LENGTH_BYTES, scratchpad))
	{
		return CRC_ERROR;
	}

	int16_t raw = (scratchpad[1] << 8) | scratchpad[0];
	*temp = raw / 16.0f;
	return EOK;
}

int search(uint8_t *rom)
{
	int id_bit_nr = 1;		//what bit of the ROM
	int last_zero = 0;
	int rom_byte_nr = 0;	//what byte of the ROM
	uint8_t rom_byte_mask = 1;
	uint8_t id_bit;			//actual bit
	uint8_t cmp_id_bit;		//complement of the bit
	uint8_t search_dir;

	if(last_sensor_flag)
	{
		return false; 	//no more devices to search
	}

	if(!reset())
	{
		//no devices present
		last_discrepancy = 0;
		last_sensor_flag = 0;
		last_family_discrepancy = 0;
		show_error(NO_PRESENCE_ERR);
	}

	write_byte(SEARCH_ROM_CMD);		//0xF0

	while(rom_byte_nr < ROM_LENGTH_BYTES)
	{
		id_bit = read_bit();
		cmp_id_bit = read_bit();

		//check if no sensors
		if(id_bit == 1 && cmp_id_bit == 1)
		{	
			//no connection to sensors
			break;
		}

		//all sensors coupled have 0 or 1
		if(id_bit != cmp_id_bit)
		{
			search_dir = id_bit;	//no conflict
		} else {
			//conflict, choose based on last discrepancy
			if(id_bit_nr < last_discrepancy)
			{
				search_dir = ((rom_nr[rom_byte_nr] & rom_byte_mask) > 0);
			}
			else {
				search_dir = (id_bit_nr == last_discrepancy);
			}

			//record the position as last_zero
			if(search_dir == 0)
			{
				last_zero = id_bit_nr;
				if(last_zero < 9)
				{
					last_family_discrepancy = last_zero;
				}
			}
		}

		//set or clear bit in rom_nr
		if(search_dir == 1)
		{
			rom_nr[rom_byte_nr] |= rom_byte_mask;
		}
		else {
			rom_nr[rom_byte_nr] &= ~rom_byte_mask;
		}

		write_bit(search_dir);

		id_bit_nr++;
		rom_byte_mask <<= 1;	//next bit in byte

		if(rom_byte_mask == 0)
		{
			rom_byte_nr++;
			rom_byte_mask = 1;
		}
	}

	last_discrepancy = last_zero;
	
	//check last sensor
	if(last_discrepancy == 0)
	{
		last_sensor_flag = 1;
	}

	for(int i = 0; i < ROM_LENGTH_BYTES; i++)
	{
		rom[i] = rom_nr[i];
	}

	return true;	//success
}