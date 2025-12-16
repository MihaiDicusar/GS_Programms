/**
* @file output_led.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of output_led module
*/

#ifndef OUTPUT_LED_H
#define OUTPUT_LED_H

#define D23             7
#define D22             6
#define D21             5

/**
* @brief This updates the GPIOD LEDs based on step counter
* @param value - value from step counter
* @return void
*/
void update_LED_GPIOD(int value);

/**
* @brief This function updates the GPIOE LEDs based on direction
* @param direction - direction
* @return void
*/
void update_LED_GPIOE(int direction);

/**
* @brief This function is used to turn GPIOE LED off
* @param pin - LED that needs to be turned off
* @return void
*/
void turn_off_LED_GPIOE(int pin);

/**
* @brief This function is used to turn GPIOE LED on
* @param pin - LED that needs to be turned on
* @return void
*/
void turn_on_LED_GPIOE(int pin);

void turn_on_LED_GPIOD(int pin);
void turn_off_LED_GPIOD(int pin);

#endif