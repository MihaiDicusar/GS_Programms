/**
* @file phase.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of phase module
*/

#ifndef PHASE_H
#define PHASE_H

#define PHASE_A     1
#define PHASE_B     2
#define PHASE_C     3
#define PHASE_D     4

/**
* @brief This function gives the phase based on inputs from
*        channel A and B
* @param inputA - value from Channel A
* @param inputB - value from Channel B
* @return RESULT_OK if succesful
*/
int givePhase(int *phase, int inputA, int inputB);

#endif