/**
* @file fsm.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of fsm module
*/

#ifndef FSM_H
#define FSM_H

#define FORWARD_DIR     1
#define BACKWARD_DIR    2
#define NO_CHANGE_DIR   3
#define ERROR_DIR       -1

/**
* @brief This function gives the direction based on last and current phase
* @param last_phase - value from last phase
* @param current_phase - value of current phase
* @return RESULT_OK if succesful
*         GENERAL_ERROR if ERROR_DIR, aka a phase was skipped
*/
int giveDirection(int *direction, int last_phase, int current_phase);

#endif