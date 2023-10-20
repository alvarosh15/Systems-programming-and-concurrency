/*
 * Hotel.c
 *
 *  Created on: 9 abr. 2021
 *      Author: RZP
 */

#include "Hotel.h"
#include "Planta.h"
#include "Planta.c"

/**
 * crea un hotel como un array de NPlantas cada una de ellas una lista de habitaciones
 * vacía
 */
void crearHotel(ListaHab* h,unsigned NPlantas) {
	for(int i = 0; i < NPlantas; i++) {
		crear(&(h[i]));
	}
}
/**
 * añade a la lista de clientes del hotel h que tiene NPlantas un nuevo cliente en
 * la habitacion nh (en la planta nh/10) con el nombre y fecha de salida de los parámetros
 * El cliente no se añade si el nh/10 no es una planta del hotel o si la fecha no es un valor
 * de un día del mes (entre 1 y 31)
 */
void nuevoClienteHotel(ListaHab *h,unsigned NPlantas,unsigned nh,char *nombre,unsigned fs) {
	if((nh / 10) < NPlantas && fs > 0 && fs < 32) {
		int planta = nh / 10;
		nuevoCliente(&(h[planta]), nh, nombre, fs);	
	}
}
/*
 * Se imprimen todos los clientes del hotel h que tiene NPlantas
 */
void imprimirHotel(ListaHab *h,unsigned NPlantas) {
	for(int i = 0; i < NPlantas; i++) {
		printf("\nPlanta %i", i);
		imprimir(h[i]);
	}
}
/**
 * Se borran todos los clientes del hotel h que tiene NPlantas
 */
void borrarHotel(ListaHab *h,unsigned NPlantas) {
	for(int i = 0; i < NPlantas; i++) {
		borrar(&(h[i]));
	}
}
/**
 * Se borran todos los clientes que tienen como fecha de salida fs del hotel
 * h que tiene NPlantas
 */
void borrarFechaSalidaHotel(ListaHab *h,unsigned NPlantas,unsigned fs) {
	for(int i = 0; i < NPlantas; i++) {
		borrarFechaSalida(&(h[i]), fs);
	}
}
