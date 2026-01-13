/**
* @file custom_error.h
* @author Mihai Dicusar
* @date Jan 2026
* @brief Header file of custom_error module
*/

#ifndef CUSTOM_ERROR_H
#define CUSTOM_ERROR_H

#define EOK              0
#define NO_PRESENCE_ERR -1
#define INVALID_ROM     -2
#define CRC_ERROR       -3

/**
* @brief This function displays an error based on error code
* @param error_code the error code that selects what error
*                   will be displayed
* @return void
*/
void show_error(int error_code);

#endif