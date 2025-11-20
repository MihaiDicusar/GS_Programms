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
                 
                return INT_OVERFLOW_ERROR;
            }
        int sum = firstNumber + secondNumber;
        push(sum);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
        return secondReturnVal;
    }

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
                
                return INT_OVERFLOW_ERROR;
            }
        int diff = secondNumber - firstNumber;
        push(diff);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
        return secondReturnVal;
    }
      
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
                 
                return INT_OVERFLOW_ERROR;
            }
        int prod = firstNumber * secondNumber;
        push(prod);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
        return secondReturnVal;
    }
    
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
            
            return DIV0_ERROR;
        } else if (secondNumber == INT_MIN && firstNumber == -1)
        {
            
            return INT_OVERFLOW_ERROR;
        }
        int quot = secondNumber / firstNumber;
        push(quot);
        return RESULT_OK;
    }
    if (firstReturnVal == 0)
    {
        push(firstNumber);
        return secondReturnVal;
    }
    return STACK_UNDERFLOW_ERROR;
}

int print()
{
    clearStdout();
    if(getSize() > 0)
    {
        outputAsString(buffer, getValueFromStack(1));
        strcat(buffer, "\n");
        printStdout(buffer);
    }
    return RESULT_OK;
}

int printAll()
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
        return RESULT_OK;

}

int clear()
{
    clearStack();
    clearStdout();
    return RESULT_OK;
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
        return secondReturnVal;
    }
    
    return firstReturnVal;
}

int duplicate()
{
    int returnVal;
    firstReturnVal = pop(&firstNumber);
    if (firstReturnVal == 0)
    {
        push(firstNumber);
        
        returnVal = push(firstNumber);
        return returnVal;
    }
    
    return firstReturnVal;
}
