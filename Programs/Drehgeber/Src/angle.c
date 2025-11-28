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

void updateCounter(int direction)
{
    if (direction == FORWARD_DIR)
    {
        counter++;
    }
    else if (direction == BACKWARD_DIR)
    {
        counter++;
    }
}

void updatePhaseCounter(int direction)
{
    if (direction == FORWARD_DIR)
    {
        phaseCounter++;
    }
    else if (direction == BACKWARD_DIR)
    {
        phaseCounter++;
    }
}

int getPhaseCounter()
{
    return phaseCounter;
}

void resetCounter()
{
    counter = 0;
}

void resetPhaseCounter()
{
    phaseCounter = 0;
}
