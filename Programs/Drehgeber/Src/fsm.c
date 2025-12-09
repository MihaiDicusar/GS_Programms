/**
* @file fsm.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module gives the direction of the rotary encoder
*		 based on last phase and current phase.
*/

#include "phase.h"
#include "error_handler.h"
#include "fsm.h"

int giveDirection(int *direction, int last_phase, int current_phase)
{
    if ((last_phase == PHASE_B && current_phase == PHASE_A) ||
		(last_phase == PHASE_A && current_phase == PHASE_D) ||
		(last_phase == PHASE_D && current_phase == PHASE_C) ||
		(last_phase == PHASE_C && current_phase == PHASE_B)) 
		{
			*direction = BACKWARD_DIR;
		}
    else if ((last_phase == PHASE_B && current_phase == PHASE_C) ||
			 (last_phase == PHASE_A && current_phase == PHASE_B) ||
			 (last_phase == PHASE_D && current_phase == PHASE_A) ||
			 (last_phase == PHASE_C && current_phase == PHASE_D)) 
		{
		    *direction = FORWARD_DIR;
		}
    else if (last_phase == current_phase) 
		{
			*direction = NO_CHANGE_DIR;
		}
    else
		{
			*direction = ERROR_DIR;
            return GENERAL_ERROR;
		}
    return RESULT_OK;
}