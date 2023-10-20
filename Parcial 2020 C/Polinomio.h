/*
 * Polinomio.h
 *
 *  Created on: 15 abr. 2020
 *      Author: mmar
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef POLINOMIO_H_
#define POLINOMIO_H_

typedef struct TNodo* TPolinomio;
struct TNodo{
	unsigned int coef;
	unsigned int exp;
	TPolinomio sig;
};
//PRIMERA PARTE

/*Crea el polinomio 0 (es decir, un polinomio vacío).
*/
void polinomioCero(TPolinomio *p);

/*Devuelve el grado del polinomio, es decir, el mayor exponente de los
* monomios que no son nulos. En el ejemplo, el grado es 7.
*/
int grado(TPolinomio p);

/* Devuelve el coeficiente de exponente exp del polinomio p.
*/
int coeficiente(TPolinomio p,unsigned int exp);

/* Insertar el monomio con coeficiente coef, y exponente exp en el polinomio,
 * de manera que el polinomio quede ordenado.
 * Asegurarse que no se insertan monomios cuyo coeficiente sea 0 y
 * tampoco dos monomios con el mismo exponente.
 * Si al insertar un monomio ya hay otro con el mismo exponente
 * los coeficientes se sumarán. Se puede asumir que el valor del coeficiente coef a
 *  sumar siempre será un número natural (un entero no negativo)
*/
void insertar(TPolinomio *p,unsigned int coef,unsigned int exp);

/*Escribe por la pantalla el polinomio con un formato similar al siguiente:
* [(9,0)(5,1)(3,3)(2,5)(3,7)] para el polinomio ejemplo.
*/
void imprimir(TPolinomio p);


/* Elimina todos los monomios del polinomio haciendo
 * que el polinomio resultante sea el polinomio 0.
*/
void destruir(TPolinomio *p);

// FIN PRIMERA PARTE

// SEGUNDA PARTE

/* Lee los coeficientes de un polinomio que están almacenados en
* un fichero de texto, y crean la lista de monomios p.
* Los coeficientes en el fichero de texto van de menor exponente a mayor exponente
* y son dígitos del 0 al 9.
* Por ejemplo, para el polinomio ejemplo el fichero de texto estaría compuesto por
* la secuencia de caracteres “95030203”. La conversión de un valor de tipo ‘char’
* que contenga un valor númerico (ej. char c = ‘2’) a su correspondiente valor
* entero (int valor), se puede hacer de la siguiente forma: valor = c – ‘0’.
*/
void crearDeFichero(TPolinomio *p, char *nombre);


// FIN SEGUNDA PARTE

// TERCERA PARTE


/* Evalúa el polinomio para el valor x y devuelve el resultado.
 * Para la evaluación del polinomio considera utilizar un algoritmo
 * recursivo que implemente el método de Horner, de manera que
 *  "e + dx + cx^2 + bx^3 + ax^4"
 * puede evaluarse en un valor cualquiera x teniendo en cuenta que es equivalente a
 * "e + (d + (c + (b + (a)x)x)x)x".
 */
//int evaluar(TPolinomio p,int x);




#endif /* POLINOMIO_H_ */
