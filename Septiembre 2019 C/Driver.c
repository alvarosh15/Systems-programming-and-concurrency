/*
 ============================================================================
 Nombre y Apellidos:
 DNI:
 Titulación y Grupo:
 Ordenador:
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Componentes.h"

/*
-----------DEFINICION DE LA RUTINA main-----------------
*/

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int opcion;
	int salir = 0;
	long codigo;
	char texto[33];

	/*
	-----------------VARIABLES GLOBALES---------------------
	*/
	Lista listaComponentes;

	listaComponentes = Lista_Crear();

	/*
	Para realizar el menu de seleccion, utilizamos un bucle while que solo terminara cuando
	la variable "salir" sea verdadera (contenga un 1), cosa que sucedera cuando se introduzca
	por teclado un valor distinto de 1,2,3,4 o 5.
	*/
	while (!salir) {
		printf("*************************************************************************\n");
		printf("*   SELECCIONE LA OPERACION QUE DESEE REALIZAR Y PULSE INTRO            *\n");
		printf("*************************************************************************\n");
		printf("*   '1' Para anadir un nuevo componente al final de la lista            *\n");
		printf("*   '2' Para borrar el ultimo componente de la lista                    *\n");
		printf("*   '3' Para salvar la lista en fichero                                 *\n");
		printf("*   '4' Para vaciar por completo la lista                               *\n");
		printf("*   '5' Para imprimir la lista                                          *\n");
		printf("*   '6' Para salir del programa                                         *\n");
		printf("*************************************************************************\n");
		scanf("%d", &opcion);

		switch (opcion) {
		case 1: Adquirir_Componente(&codigo,texto);
				Lista_Agregar(&listaComponentes,codigo,texto);
				Lista_Imprimir(listaComponentes);
				break;
		case 2: Lista_Extraer(&listaComponentes);
				Lista_Imprimir(listaComponentes);
				break;
		case 3: Lista_Salvar(listaComponentes);
				break;
		case 4: Lista_Vaciar(&listaComponentes);
				Lista_Imprimir(listaComponentes);
				break;
		case 5: Lista_Imprimir(listaComponentes);
				break;
		default: salir = 1;
		}
	}
	/*
	Antes de salir del programa, nos aseguramos de vaciar la lista de componentes
	para que no haya fugas de memoria
	*/
	Lista_Vaciar(&listaComponentes);
	return 0;
}

// Fin fichero
// ===========
