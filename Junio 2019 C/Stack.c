/*
 * Stack.c
 *
 *  Created on: 11 jun. 2019
 *      Author: 
 */
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// Creates an empty stack.
T_Stack create() {
    T_Stack lista = NULL;
    return lista;
}

// Returns true if the stack is empty and false in other case.
int isEmpty(T_Stack q) {
    return q == NULL;
}

// Inserts a number into the stack.
void push(T_Stack * pq, int operand) {
    T_Stack nuevoNodo = malloc(sizeof(struct Node));
    nuevoNodo -> number = operand; 
    nuevoNodo -> next = NULL;

    T_Stack lista = *pq;
    while(lista -> next != NULL) {
        lista = lista -> next;
    }   
    lista -> next = nuevoNodo; 
}

// "Inserts" an operator into the stack and operates.
// Returns true if everything OK or false in other case.
int pushOperator(T_Stack * pq, char operator) {
    int ok = 0;
	T_Stack aux;
	T_Stack ptr = *pq;

	if (*pq == NULL) {
		ok = 0;
	} else {
		while (ptr->next->next != NULL) {
			ptr = ptr->next;
		}
		switch (operator) {
		case '+':
			ptr->number = ptr->next->number + ptr->number;
			aux = ptr->next;
			free(aux);
			ptr->next = NULL;
			ok = 1;
			break;
		case '-':
			ptr->number = ptr->next->number - ptr->number;
			aux = ptr->next;
			free(aux);
			ptr->next = NULL;
			ok = 1;
			break;
		case '*':
			ptr->number = ptr->next->number * ptr->number;
			aux = ptr->next;
			free(aux);
			ptr->next = NULL;
			ok = 1;
			break;
		case '/':
			ptr->number = ptr->next->number / ptr->number;
			aux = ptr->next;
			free(aux);
			ptr->next = NULL;
			ok = 1;
			break;
		default:
			ok = 0;
		}
	}
	return ok;
}

// Puts into data the number on top of the stack, and removes the top.
// Returns true if everything OK or false in other case.
int pop(T_Stack * pq, int * data) {
    int ok = 0;

    if(*pq != NULL) {
        if((*pq) -> next == NULL) {
            free(*pq);
        } else {
            T_Stack ant = *pq;
            T_Stack ptr = (*pq) -> next; 
            while(ptr -> next != NULL) {
                ant = ant -> next;
                ptr = ptr -> next;
            }
            ant -> next = NULL;
            *data = ptr -> number;
            free(ptr);
            ok = 1;
        }
    }
    return ok;
}

// Frees the memory of a stack and sets it to empty.
void destroy(T_Stack * pq) {
    T_Stack ptr;
    while(*pq != NULL) {
        ptr = *pq;
        *pq = (*pq) -> next;
        free(ptr);
    }
}
