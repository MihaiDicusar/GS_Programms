#include <stdint.h>
#define NR_PHASE_CHANGES    1200
#define NR_SLOTS            300
#define DEGREES_PER_STEP    (360.0 / NR_PHASE_CHANGES)

double getAngle();
double getVelocity(uint32_t timeDifference);
void updateCounter(int direction);
int getCounter();
void resetCounter();
int getPhaseCounter();
void updatePhaseCounter(int direction);
void resetPhaseCounter();