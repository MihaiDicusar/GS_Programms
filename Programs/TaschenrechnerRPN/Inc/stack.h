/**
  * @file stack.h
  * @author Mihai Dicusar
  * @date Nov 2025
  * @brief Header file of stack module. 
  */

#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 10
#define STACKUNDERFLOW_ERROR    -1
#define STACKOVERFLOW_ERROR     -2

extern int stack[STACK_SIZE];
extern int counter;

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

#endif