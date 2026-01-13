/**
* @file gpiod_manip.c
* @author Mihai Dicusar
* @date Jan 2026
* @brief This module manipulates PD1 and PD0 from GPIOD
*/

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "gpiod_manip.h"

void pd1_init()
{
	GPIOD->OTYPER &= ~(1 << PD1_PIN);	//push pull mode
	GPIOD->BSRR = (1 << PD1_PIN);
}

void pd0_init()
{
	GPIOD->OTYPER |= (1 << PD0_PIN);	//open drain mode
	GPIOD->BSRR = (1 << PD0_PIN);
}

void pd0_low()
{
	GPIOD->BSRR = (1 << (PD0_PIN + 16));	//0
}

void pd0_high()
{
	GPIOD->BSRR = (1 << PD0_PIN);			//1
}

void pd0_high_strong()
{
	GPIOD->OTYPER &= ~(1 << PD0_PIN);		//push pull mode
	GPIOD->BSRR = (1 << PD0_PIN);
}

uint8_t read_pd0()
{
    return (GPIOD->IDR & (1 << 0)) ? 1 : 0;
}