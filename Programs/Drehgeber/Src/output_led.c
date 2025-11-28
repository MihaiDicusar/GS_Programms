#include "stm32f429xx.h"
#include "stm32f4xx_hal.h"   
#include "fsm.h"
#include "output_led.h"

void update_LED_GPIOE(int direction)
{
    switch (direction)
    {
        case FORWARD_DIR:
            turn_on_LED_GPIOE(D23);
            turn_off_LED_GPIOE(D22);
            turn_off_LED_GPIOE(D21);
        break;

        case BACKWARD_DIR:
            turn_on_LED_GPIOE(D22);
            turn_off_LED_GPIOE(D23);
            turn_off_LED_GPIOE(D21);
        break;

        case ERROR_DIR:
            turn_on_LED_GPIOE(D21);
            turn_off_LED_GPIOE(D23);
            turn_off_LED_GPIOE(D22);
        break;

        default:
            turn_off_LED_GPIOE(D23);
            turn_off_LED_GPIOE(D22);
            turn_off_LED_GPIOE(D21);
        break;
    }
}

void update_LED_GPIOD(int value)
{
    int led_value = value & 0xFF;       //work only with 8 lowest bits LEDs
    GPIOD->ODR = (GPIOD->ODR & ~0xFF) | led_value;      //turn of all GPIOD LEDs, then turn on based on led_value
}

void turn_off_LED_GPIOE(int pin)
{
    GPIOE->BSRR = (0x01U << pin) << 16;
}

void turn_on_LED_GPIOE(int pin)
{
    GPIOE->BSRR = (0x01U << pin);
}