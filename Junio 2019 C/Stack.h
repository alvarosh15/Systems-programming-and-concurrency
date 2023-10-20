/*
 * Stack.h
 *
 *  Created on: 11 jun. 2019
 *      Author: galvez
 */

#ifndef STACK_H_
#define STACK_H_

typedef struct Node * T_Stack;
typedef struct Node {
	struct Node * next;
	int number;
} T_Node;

// Creates an empty stack.
T_Stack create();

// Returns true if the stack is empty and false in other case.
int isEmpty(T_Stack q);

// Inserts a number into the stack.
void push(T_Stack * pq, int operand);

// "Inserts" an operator into the stack and operates.
// Returns true if everything OK or false in other case.
int pushOperator(T_Stack * pq, char operator);

// Puts into data the number on top of the stack, and removes the top.
// Returns true if everything OK or false in other case.
int pop(T_Stack * pq, int * data);

// Frees the memory of a stack and sets it to empty.
void destroy(T_Stack * pq);

#endif /* STACK_H_ */
