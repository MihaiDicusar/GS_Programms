#include "phase.h"
#include "error_handler.h"

int phaseA;
int phaseB;
int phaseC;
int phaseD;

int givePhase(int *phase, int inputA, int inputB)
{
    phaseA = (inputA == 0 && inputB == 0);
	phaseB = (inputA == 1 && inputB == 0);
	phaseC = (inputA == 1 && inputB == 1);
	phaseD = (inputA == 0 && inputB == 1);

    if (phaseA) {*phase = PHASE_A;}
	if (phaseB) {*phase = PHASE_B;}
	if (phaseC) {*phase = PHASE_C;}
	if (phaseD) {*phase = PHASE_D;}

    return RESULT_OK;
}