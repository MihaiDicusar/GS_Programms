/**
  * @file stack.c
  * @author Mihai Dicusar
  * @date Nov 2025
  * @brief This module implements a stack onto which values can be pushed,
  *        popped off it and cleared.     
  */

#include "token.h"
#include <stdio.h>
#include "stack.h"
#include "display.h"

int counter = 0;
int stack[STACK_SIZE];

int push(int number)
{
    if(counter < STACK_SIZE)
    {
        stack[counter] = number;
        counter++;
    }
    else {
        printStdout("STACK OVERFLOW ERROR\n");
        return STACKOVERFLOW_ERROR;
    }
    return 0;
}

int pop(int *value)
{
    if(counter > 0)
    {
        *value = stack[--counter];
        return 0;
    }
    else {
        return STACKUNDERFLOW_ERROR;
    }
}

void clearStack()
{
    if (counter > 0)
    {
        counter = 0;
    }
}
