/*
 * Hotel.h
 *
 *  Created on: 6 abr. 2021
 *      Author: RZP
 */
#include "Planta.h"
#ifndef HOTEL_H_
#define HOTEL_H_



/**
 * crea un hotel como un array de NPlantas cada una de ellas una lista de habitaciones
 * vacía
 */
void crearHotel(ListaHab* h,unsigned NPlantas);
/**
 * añade a la lista de clientes del hotel h que tiene NPlantas un nuevo cliente en
 * la habitacion nh (en la planta nh/10) con el nombre y fecha de salida de los parámetros
 * El cliente no se añade si el nh/10 no es una planta del hotel o si la fecha no es un valor
 * de un día del mes (entre 1 y 31)
 */
void nuevoClienteHotel(ListaHab *h,unsigned NPlantas,unsigned nh,char *nombre,unsigned fs);
/*
 * Se imprimen todos los clientes del hotel h que tiene NPlantas
 */
void imprimirHotel(ListaHab *h,unsigned NPlantas);
/**
 * Se borran todos los clientes del hotel h que tiene NPlantas
 */
void borrarHotel(ListaHab *h,unsigned NPlantas);
/**
 * Se borran todos los clientes que tienen como fecha de salida fs del hotel
 * h que tiene NPlantas
 */
void borrarFechaSalidaHotel(ListaHab *h,unsigned NPlantas,unsigned fs);

/**
* Se almacena en el hotel con nPlantas, los clientes almacenados en el fichero de texto nombre.
* En el fichero los clientes vienen con el siguiente formato
* Nombre1 numHab1 fechaSal1
* Nombre2 numHab2 fechaSal2
* ...
* Observa que en el fichero viene antes el nombre del cliente que el n�mero
* de habitaci�n (al contrario que en la funcion nuevoClienteHotel)
*/

#endif /* HOTEL_H_ */
