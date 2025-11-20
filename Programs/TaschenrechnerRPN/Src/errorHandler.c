
#include "errorHandler.h"
#include "display.h"


void errorHandler(int fehlerCode){
    switch(fehlerCode){
        case DIV0_ERROR:
            printStdout("STACK UNDERFLOW ERROR\n"); 
            break;

        case INT_OVERFLOW_ERROR:
            printStdout("INT OVERFLOW ERROR\n");
            break;

        case STACK_UNDERFLOW_ERROR:
            printStdout("STACK UNDERFLOW ERROR\n");
            break;
            
        case STACK_OVERFLOW_ERROR:
            printStdout("STACK OVERFLOW ERROR\n");
            break;
            
        case INPUT_OVERFLOW_ERROR:
                printStdout("INPUT OVERFLOW ERROR\n");  
                break;

        default:


    }
}