/**
* @file angle.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of display_output module
*/

#ifndef DISPLAY_OUTPUT_H
#define DISPLAY_OUTPUT_H

#define ANGLE_TEXT_POS_X    1
#define ANGLE_TEXT_POS_Y    1
#define ANGLE_NR_POS_X      20
#define ANGLE_NR_POS_Y      1
#define DEG_POS_X           28
#define DEG_POS_Y           1
#define ANG_VEL_TEXT_POS_X  1
#define ANG_VEL_TEXT_POS_Y  3
#define ANG_VEL_NR_POS_X    20
#define ANG_VEL_NR_POS_Y    3
#define DEG_S_POS_X         28
#define DEG_S_POX_Y         3

/**
* @brief This function display the initial text
* @return void
*/
void display_init();

/**
* @brief This function displays the angle
* @param angle - angle to be displayed
* @return void
*/
void display_angle(double angle);

/**
* @brief This function displays the angular velocity
* @param velocity - angular velocity to display
* @return void
*/
void display_velocity(double velocity);

#endif