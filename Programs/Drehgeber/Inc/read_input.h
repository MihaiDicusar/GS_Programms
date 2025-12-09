/**
* @file read_input.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of read_input module
*/

#ifndef READ_INPUT_H
#define READ_INPUT_H

#define S6_PRESSED      1
#define S6_NOT_PRESSED  0

/**
* @brief This function gives the input from Channel A
* @return RESULT_OK if succesful
*/
int givePinA(int *result);

/**
* @brief This function gives the input from Channel B
* @return RESULT_OK if succesful
*/
int givePinB(int *result);

/**
* @brief This function checks if S6 button(used for reseting an error)
*        has been pressed
* @return S6_PRESSED if pressed
*         s6_NOT_PRESSED if not pressed
*/
int check_if_s6_pressed();

#endif