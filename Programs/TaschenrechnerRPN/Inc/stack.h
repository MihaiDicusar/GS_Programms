/**
  * @file stack.h
  * @author Mihai Dicusar
  * @date Nov 2025
  * @brief Header file of stack module. 
  */

#ifndef STACK_H
#define STACK_H

/**
*  @brief This function pushes the value of the token NUMBER onto the top of the stack
*  @return 0 if succesful or STACKOVERFLOW_ERROR when a value is pushed onto a full stack
 */
int push(int number);

/**
*  @brief This function pops the value that is located at the top of the stack for further operations
*  @return 0 if succesful, else STACKUNDERFLOW_ERROR when not enough values for operations
 */
int pop(int *result);

/**
* @brief This function clears the stack by reseting the counter to 0
* @return void
*/
void clearStack(void);

/**
* @brief This function returns the value from the stack at position given in the parameter.
* @return value at position "pos" from the stack
*/
int getValueFromStack(int pos);

/**
* @brief This function returns the size of the stack
* @return size of the stack
*/
int getSize();

#endif