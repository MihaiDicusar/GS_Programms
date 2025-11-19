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
#include "custom_errors.h"

#define STACK_SIZE 10

static int size = 0;
static int stack[STACK_SIZE];

int push(int number)
{
    if(size < STACK_SIZE)
    {
        stack[size] = number;
        size++;
    }
    else {
        printStdout("STACK OVERFLOW ERROR\n");
        return STACK_OVERFLOW_ERROR;
    }
    return RESULT_OK;
}

int pop(int *value)
{
    if(size > 0)
    {
        *value = stack[--size];
        return RESULT_OK;
    }
    else {
        return STACK_UNDERFLOW_ERROR;
    }
}

int getValueFromStack(int pos)
{
    if(size > 0)
    {
        return stack[size - pos];
    }
}

int getSize()
{
    return size;
}

void clearStack()
{
    if (size > 0)
    {
        size = 0;
    }
}
