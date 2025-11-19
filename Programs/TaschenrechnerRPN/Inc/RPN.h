/**
  * @file RPN.h
  * @author Mihai Dicusar
  * @date Nov 2025
  * @brief Header file of RPN module. 
  */

#ifndef RPN_H
#define RPN_H

/**
* @brief This function pops the first two values from the stack
*        and summarizes them. Then the result is pushed back onto the stack.
* @return 0 if succesful
          STACKUNDERFLOW_ERROR if not enough values for this operation can be popped
          INT_OVERFLOW_ERROR if an arithmetic overflow occurs
*/
int add();

/**
* @brief This function pops the first two values from the stack
*        and the first value is subtracted from second value. 
*        Then the result is pushed back onto the stack.
* @return 0 if succesful
          STACKUNDERFLOW_ERROR if not enough values for this operation can be popped
          INT_OVERFLOW_ERROR if an arithmetic overflow occurs
*/
int subtract();

/**
* @brief This function pops the first two values from the stack
*        and multiplies them. Then the result is pushed back onto the stack.
* @return 0 if succesful
          STACKUNDERFLOW_ERROR if not enough values for this operation can be popped
          INT_OVERFLOW_ERROR if an arithmetic overflow occurs
*/
int multiply();

/**
* @brief This function pops the first two values from the stack
*        and the second value is divided by the first value. 
*        Then the result is pushed back onto the stack
* @return 0 if succesful
*         STACKUNDERFLOW_ERROR if not enough values for this operation can be popped
*         INT_OVERFLOW_ERROR if an arithmetic overflow occurs
*/
int divide();

/**
* @brief This function prints the first value from the stack to the stdout terminal
* @return void
*/
void print();

/**
* @brief This function prints all the values from the stack to the stdout terminal
* @return void
*/
void printAll();

/**
* @brief This function clears the stack and the stdout terminal
* @return void
*/
void clear();

/**
* @brief This function pops the first two values from the stack
*        and switches them, thus initial first value will be placed 
*        on second place and the initial second value will be placed
*        on the first place.
* @return 0 if succesful
*         STACKUNDERFLOW_ERROR if not enough values for this operation can be popped
*/
int swap();

/**
* @brief This function pops the first value from the stack and duplicates it,
         so first two places of the stack have the same value.
* @return 0 if succesful
*         STACKUNDERFLOW_ERROR if not enough values for this operation can be popped
*/
int duplicate();

/**
* @brief This function shows an input overflow error on display, for example when the user is
         inserting 2147483648.
* @return INPUT_OVERFLOW_ERROR if number from input is too large
*/
int showOverflowError();

#endif