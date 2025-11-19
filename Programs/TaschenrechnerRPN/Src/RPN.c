/**
  * @file RPN.c
  * @author Mihai Dicusar
  * @date Nov 2025
  * @brief This module implements RPN functions that take values from stack
  *        and manipulates them, such as addition, subtraction, multiplication,
           division, duplicating, swapping, as well as printing them on the terminal.
           Also clearing the terminal and the stack is possible.
  */

#include "token.h"
#include "limits.h"
#include "display.h"
#include <stdio.h>
#include "stack.h"
#include "RPN.h"
#include "output_print.h"
#include <string.h>
#include "custom_errors.h"

int firstNumber;
int secondNumber;
int firstReturnVal;
int secondReturnVal;
static char buffer[20];

int add()
{
    firstReturnVal = pop(&firstNumber);
    secondReturnVal = pop(&secondNumber);
    if (firstReturnVal == 0 && secondReturnVal == 0)
    {
        if ((firstNumber > 0 && secondNumber > 0 && firstNumber > INT_MAX - secondNumber) ||
            (firstNumber < 0 && secondNumber < 0 && firstNumber < INT_MIN - secondNumber))
            {
                printStdout("INT OVERFLOW ERROR\n"); 
                return INT_OVERFLOW_ERROR;
            }
        int sum = firstNumber + secondNumber;
        push(sum);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
    }
    printStdout("STACK UNDERFLOW ERROR\n");
    return STACK_UNDERFLOW_ERROR;   
}

int subtract()
{
    firstReturnVal = pop(&firstNumber);
    secondReturnVal = pop(&secondNumber);
    if (firstReturnVal == 0 && secondReturnVal == 0)
    {
        if ((secondNumber > 0 && firstNumber < 0 && secondNumber > INT_MAX + firstNumber) ||
            (secondNumber < 0 && firstNumber > 0 && secondNumber < INT_MIN + firstNumber))
            {
                printStdout("INT OVERFLOW ERROR\n"); 
                return INT_OVERFLOW_ERROR;
            }
        int diff = secondNumber - firstNumber;
        push(diff);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
    }
    printStdout("STACK UNDERFLOW ERROR\n");  
    return STACK_UNDERFLOW_ERROR; 
}

int multiply()
{
    firstReturnVal = pop(&firstNumber);
    secondReturnVal = pop(&secondNumber);
    if (firstReturnVal == 0 && secondReturnVal == 0)
    {
        if ((firstNumber != 0 && secondNumber != 0) &&
            (firstNumber > 0 && secondNumber > 0 && firstNumber > INT_MAX / secondNumber) ||
            (firstNumber > 0 && secondNumber < 0 && secondNumber < INT_MIN / firstNumber) ||
            (firstNumber < 0 && secondNumber > 0 && firstNumber < INT_MIN / secondNumber) ||
            (firstNumber < 0 && secondNumber < 0 && firstNumber < INT_MAX / secondNumber))
            {
                printStdout("INT OVERFLOW ERROR\n"); 
                return INT_OVERFLOW_ERROR;
            }
        int prod = firstNumber * secondNumber;
        push(prod);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
    }
    printStdout("STACK UNDERFLOW ERROR\n"); 
    return STACK_UNDERFLOW_ERROR;    
}

int divide()
{
    firstReturnVal = pop(&firstNumber);
    secondReturnVal = pop(&secondNumber);
    if (firstReturnVal == 0 && secondReturnVal == 0)
    {
        if (firstNumber == 0)
        {
            printStdout("DIVISION/0 ERROR\n");
            return DIV0_ERROR;
        } else if (secondNumber == INT_MIN && firstNumber == -1)
        {
            printStdout("INT OVERFLOW ERROR\n");
            return INT_OVERFLOW_ERROR;
        }
        int quot = secondNumber / firstNumber;
        push(quot);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
    }
    printStdout("STACK UNDERFLOW ERROR\n"); 
    return STACK_UNDERFLOW_ERROR;
}

void print()
{
    clearStdout();
    if(getSize() > 0)
    {
        outputAsString(buffer, getValueFromStack(1));
        strcat(buffer, "\n");
        printStdout(buffer);
    }
}

void printAll()
{
    clearStdout();
    if(getSize() > 0)
    {
        for(int i = 1; i <= getSize(); i++)
        {
            outputAsString(buffer, getValueFromStack(i));
            strcat(buffer, "\n");
            printStdout(buffer);
        }
    }
}

void clear()
{
    clearStack();
    clearStdout();
}

int swap()
{
    firstReturnVal = pop(&firstNumber);
    secondReturnVal = pop(&secondNumber);
    if (firstReturnVal == 0 && secondReturnVal == 0)
    {
        push(firstNumber);
        push(secondNumber);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
    }
    printStdout("STACK UNDERFLOW ERROR\n"); 
    return STACK_UNDERFLOW_ERROR;
}

int duplicate()
{
    firstReturnVal = pop(&firstNumber);
    if (firstReturnVal == 0)
    {
        push(firstNumber);
        push(firstNumber);
        return RESULT_OK;
    }
    printStdout("STACK UNDERFLOW ERROR\n");  
    return STACK_UNDERFLOW_ERROR; 
}

int showOverflowError()
{
    printStdout("INPUT OVERFLOW ERROR\n");  
    return INPUT_OVERFLOW_ERROR;
}