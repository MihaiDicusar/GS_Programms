/**
* @file angle.h
* @author Mihai Dicusar
* @date Dec 2025
* @brief Header file of angle module
*/

#ifndef ANGLE_H
#define ANGLE_H

#include <stdint.h>
#define NR_PHASE_CHANGES    1200
#define NR_SLOTS            300
#define DEGREES_PER_STEP    (360.0 / NR_PHASE_CHANGES)

/**
* @brief This function calculates the angle based on step counter
*        and degrees per step
* @return angle as double
*/
double getAngle();

/**
* @brief This function calculates the angular velocity based on
*        phase counter, degrees per step and time difference
* @param timeDifference - needed for calculation of angular velocity
* @return angular velocity as double
*/
double getVelocity(uint32_t timeDifference);

/**
* @brief This function updates the step counter if direction is
*        forwards or backwards
* @param direction - forwards to increment, backwards to decrement
* @return void
*/
void updateCounter(int direction);

/**
* @brief This function updates the phase counter if direction
*        is forwards or backwards
* @param direction - increments phase counter if it's forwards or backwards
* @return void
*/
void updatePhaseCounter(int direction);

/**
* @brief This function is a getter for step counter
* @return counter as int
*/
int getCounter();

/**
* @brief This function resets the step counter
* @return void
*/
void resetCounter();

/**
* @brief This function is a getter for phase counter
* @return phase counter as int
*/
int getPhaseCounter();

/**
* @brief This function resets phase counter
* @return void
*/
void resetPhaseCounter();

#endif