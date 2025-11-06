/**
  * @file RPN.c
  * @author Mihai Dicusar
  * @date Nov 2025
  * @brief This module implements the conversion of int values
  *        into a string. The terminal requires it for output.
  */

#include "display.h"
#include "limits.h"

#define BUF_LENGTH 20

void outputAsString(char* buffer, int value)
{
    //when value is '0' 
    if (value == 0)     
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    char tempString[BUF_LENGTH];
    int i = 0;
    int isNegative = (value < 0) ? true : false;

    while (value != 0)
    {
        int rest = value % 10;

        //force rest to be positive
        if (rest < 0)   
        {
            rest *= -1;
        }
        value /= 10;

        tempString[i] = '0' + rest;
        i += 1;
    }

    //add negative sign for negative value
    if (isNegative)
    {
        tempString[i] = '-';    
        i += 1;
    }

    //write value to buffer in reverse order
    for (int j = 0; j < i; j++)
    {
        int buffer_index = (i - 1) - j;
        buffer[j] = tempString[buffer_index];
    }

    buffer[i] = '\0';
}