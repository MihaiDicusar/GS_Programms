/**
* @file angle.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module calculates the angle and the angular velocity,
*        updates or resets the counter or phase counter.
*/

#include "fsm.h"
#include "angle.h"

int counter = 0;
int phaseCounter = 0;

double getAngle()
{
    double angle = (counter * DEGREES_PER_STEP);
    return angle;
}

double getVelocity(uint32_t timeDifference)
{
    double velocity = (double)(phaseCounter * DEGREES_PER_STEP) / (double)(timeDifference / 1000.0);
    return velocity;
}

int getCounter()
{
    return counter;
}

int getPhaseCounter()
{
    return phaseCounter;
}

void updateCounter(int direction)
{
    if (direction == FORWARD_DIR)
    {
        counter++;
    }
    else if (direction == BACKWARD_DIR)
    {
        counter--;
    }
}

void updatePhaseCounter(int direction)
{
    if (direction == FORWARD_DIR || direction == BACKWARD_DIR)
    {
        phaseCounter++;
    }
}

void resetCounter()
{
    counter = 0;
}

void resetPhaseCounter()
{
    phaseCounter = 0;
}
