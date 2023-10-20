/*
 * Principal.c
 *
 *  Created on: 28 abr. 2020
 *      Author: mmar
 */
#include "Polinomio.h"
#include <stdio.h>

/* Dados dos polinomios p1 y p2, devuelve 1 si todos
 * los monomios del polinomio p2 son también monomios del polinomio p1,
 * y 0 en caso contrario. ImpLementar este algoritmo utilizando
 * solo funciones de “Polinomio.h�
*/

//int incluye(TPolinomio p1,TPolinomio p2);

int main(void) {
	//PARTE 1
	//setvbuf(stdout,NULL,_IONBF,0);
	TPolinomio p;
	int g,c;

	//Creamos polinomio cero
	polinomioCero(&p);

	/* Insertamos monomios para crear el siguiente polinomio:
	 *  [(3,7)(0,6)(2,5)(0,4)(3,3)(0,2)(5,1)(9,0)]
	*/
	insertar(&p,2,5);
	insertar(&p,9,0);
	insertar(&p,3,7);
	insertar(&p,3,3);
	insertar(&p,0,2);
	insertar(&p,4,1);
	insertar(&p,1,1);
	insertar(&p,0,4);

	//Mostramos el grado del polinomio
	g = grado(p);
	printf("El grado del polinomio es: %d\n", g);
	printf("COMPRUEBA QUE SEA 7\n");

	//Imprimirmos el polinomio
	printf("\nEl polinomio creado es: ");
	imprimir(p);
	printf("COMPRUEBA QUE SEA: [(9,0)(5,1)(3,3)(2,5)(3,7)]\n");

	//Imprimimos el coeficiente de varios monomios
	c = coeficiente(p,5);
	printf("\nEl coeficiente para el exp 5 es: %d\n", c);
	printf("COMPRUEBA QUE SEA 2\n");

	c = coeficiente(p,6);
	printf("El coeficiente para el exp 6 es: %d\n", c);
	printf("COMPRUEBA QUE SEA 0\n");

	c = coeficiente(p,0);
	printf("El coeficiente para el exp 0 es: %d\n", c);
	printf("COMPRUEBA QUE SEA 9\n");

	//PARTE 2
	TPolinomio p2;

	polinomioCero(&p2);
	crearDeFichero(&p2,"monomios.txt");
	printf("\nPolinomio 2 creado desde fichero: ");
	imprimir(p2);

	//PARTE 3

/*	TPolinomio p3;

	polinomioCero(&p3);
	insertar(&p3,2,5);
	insertar(&p3,3,3);
	insertar(&p3,5,1);
	printf("\nPolinomio 1: ");
	imprimir(p);
	printf("Polinomio 2: ");
	imprimir(p3);
	int esta = incluye(p,p3);
	if (esta){
		printf("Los monomios del Polinomio 1 incluyen a los del Polinomio 2\n");
	}else{
		printf("Los monomios del Polinomio 1 no incluyen a los del Polinomio 2\n");
	}
	printf("COMPRUEBA QUE INDIQUE QUE NO INCLUYEN\n");

	printf("\n");
	imprimir(p2);
	int valor = evaluar(p2,3);
	printf("El valor del polinomio para x = 3 es: %d\n", valor);
	printf("COMPRUEBA QUE SEA 7152\n");
*/
	destruir(&p);

	return 0;
}


