/**
* @file button_input.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of button_input module
*/

#ifndef BUTTON_INPUT_H
#define BUTTON_INPUT_H

#define IDR_MASK_PIN_7      (0x01U << 7)

/**
* @brief This method checks if S7 is pressed
* @return void
*/
void pollUntilButtonPressed();

#endif