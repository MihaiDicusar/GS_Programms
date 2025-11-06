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

int firstNumber;
int secondNumber;
static char buffer[20];

int add()
{
    if (pop(&firstNumber) == 0 && pop(&secondNumber) == 0)
    {
        if ((firstNumber > 0 && secondNumber > 0 && firstNumber > INT_MAX - secondNumber) ||
            (firstNumber < 0 && secondNumber < 0 && firstNumber < INT_MIN - secondNumber))
            {
                printStdout("INT OVERFLOW ERROR\n"); 
                return INT_OVERFLOW_ERROR;
            }
        int sum = firstNumber + secondNumber;
        push(sum);
        return 0;
    }
    printStdout("STACK UNDERFLOW ERROR\n");   
}

int subtract()
{
    if (pop(&firstNumber) == 0 && pop(&secondNumber) == 0)
    {
        if ((secondNumber > 0 && firstNumber < 0 && secondNumber > INT_MAX + firstNumber) ||
            (secondNumber < 0 && firstNumber > 0 && secondNumber < INT_MIN + firstNumber))
            {
                printStdout("INT OVERFLOW ERROR\n"); 
                return INT_OVERFLOW_ERROR;
            }
        int diff = secondNumber - firstNumber;
        push(diff);
        return 0;
        }
    printStdout("STACK UNDERFLOW ERROR\n");   
}

int multiply()
{
    if (pop(&firstNumber) == 0 && pop(&secondNumber) == 0)
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
        return 0;
    }
    printStdout("STACK UNDERFLOW ERROR\n"); 
    
}

int divide()
{
    if (pop(&firstNumber) == 0 && pop(&secondNumber) == 0)
    {
        if (firstNumber == 0)
        {
            printStdout("DIVISION/0 ERROR\n");
            return DIV0_ERROR;
        } else if (secondNumber == INT_MIN && firstNumber == -1)
        {
            printStdout("INT OVERFLOW ERROR\n");
            return DIV0_ERROR;
        }
        int quot = secondNumber / firstNumber;
        push(quot);
        return 0;
    }
    printStdout("STACK UNDERFLOW ERROR\n"); 
}

void print()
{
    if (counter > 0)
    {
        outputAsString(buffer, stack[counter - 1]);
        strcat(buffer, "\n");
        printStdout(buffer);
    }
    
}

void printAll()
{
    for(int i = 0; i < counter; i++)
    {
        outputAsString(buffer, stack[i]);
        strcat(buffer, "\n");
        printStdout(buffer);
    }
}

void clear()
{
    clearStack();
    clearStdout();
}

int swap()
{
    if (pop(&firstNumber) == 0 && pop(&secondNumber) == 0)
    {
        push(firstNumber);
        push(secondNumber);
        return 0;
    }
    printStdout("STACK UNDERFLOW ERROR\n"); 
    return STACKUNDERFLOW_ERROR;
}

int duplicate()
{
    if (pop(&firstNumber) == 0)
    {
        push(firstNumber);
        push(firstNumber);
        return 0;
    }
    printStdout("STACK UNDERFLOW ERROR\n");  
    return STACKUNDERFLOW_ERROR; 
}