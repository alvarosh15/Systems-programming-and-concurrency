/*
 * Planta.c
 *
 *  Created on: 9 abr. 2021
 *      Author: RZP
 */


#include "Planta.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * crea una lista de habitaciones vacia
 */
void crear(ListaHab *lh) {
	*lh = NULL;
}

/**
 * En esta función se añade a la lista, la habitación con número nh,
 * cliente "nombre" y fecha de salida "fs".
 * Si ya existe una habitación numerada con nh en la lista se actualizan sus campos
 * con los nuevos valores ("nombre" y "fs").
 * Si no existe ninguna habitación con ese número, se inserta un nuevo nodo de manera que
 * la lista siempre esté ordenada con respecto a los números de las habitaciones (de
 * menor a mayor)
 */
void nuevoCliente(ListaHab *lh,unsigned nh,char *nombre,unsigned fs) {

	ListaHab nuevoNodo = malloc(sizeof(struct Nodo));
	strcpy(nuevoNodo -> nombre, nombre);
	nuevoNodo -> numHab = nh;
	nuevoNodo -> fechaSalida = fs;
	nuevoNodo -> sig = NULL;
	if(*lh == NULL) {
		*lh = nuevoNodo;
	} else {
		ListaHab ptr = *lh;
		ListaHab aux = *lh;
		int esta = 0;

		while(aux -> sig != NULL && esta == 0) {
			if(aux -> numHab == nh) {
				strcpy(aux -> nombre, nombre);
				aux -> fechaSalida = fs;
				esta = 1;
			}
			aux = aux -> sig;
		}

		if(esta == 0) {
			if((*lh) -> numHab > nh) {
				nuevoNodo -> sig = *lh;
				*lh = nuevoNodo;
			} else {
				while(ptr -> sig != NULL && nh > ptr -> sig -> numHab) {
					ptr = ptr -> sig;
				}
				nuevoNodo -> sig = ptr -> sig;
				ptr -> sig = nuevoNodo;
			}
		} 
	}
}

/**
 * Escribe por la pantalla la información de cada una de las habitaciones
 * almacenadas en la lista.
 * El formato de salida debe ser:
 * \t habitacion "nh" ocupada por "nombre" con fecha de salida "fs"
 */
void imprimir(ListaHab lh) {
	if(lh == NULL) {
		printf("Lista vacia \n");
	} else {
		while(lh != NULL) {
			printf("\n Habitacion %d ocupada por %s con fecha de salida %d", lh -> numHab, lh -> nombre, lh -> fechaSalida);
			lh = lh -> sig;
		}
	}
}

/**
 * Borra todos los nodos de la lista y la deja vacía
 */
void borrar(ListaHab *lh) {
	ListaHab ptr;
	while(*lh != NULL) {
		ptr = *lh;
		*lh = (*lh) -> sig;
		free(ptr);
	}
}

/**
 * Borra todos las habitaciones cuya fecha de salida es fs.
 */

void borrarFechaSalida(ListaHab *lh,unsigned fs) {

	ListaHab ant = NULL;
	ListaHab ptr = *lh;
	while(ptr != NULL) {
		if(ptr -> fechaSalida == fs) {
			if(ant == NULL) {
				*lh = ptr -> sig;
			} else {
				ant -> sig = ptr -> sig;
			}
			free(ptr);
		} 
		ant = ptr;
		ptr = ptr -> sig;
		
	}
}

