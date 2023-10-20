/*
 * Principal.c
 *
 *  Created on: 14/6/2016
 *      Author: 
 */

#include "ListaJugadores.h"
#include <stdio.h>



// Lee el fichero y lo introduce en la lista
void cargarFichero (char * nombreFich, TListaJugadores *lj)
{
	FILE *archivo = fopen(nombreFich, "rb");

	if(archivo == NULL) {
		perror("No se ha podido abrir el fichero.");
	} else {
		int num;
		while (fread(&num, sizeof(int), 1, archivo) == 1) {
			fread(&num, sizeof(int), 1, archivo);
			insertar(&*lj, num);
			fread(&num, sizeof(unsigned int), 1, archivo);
		}

		fclose(archivo);
	}
}


int main(){

	TListaJugadores lj;
	crear(&lj);
    unsigned int num_goles;
	cargarFichero ("goles.bin",&lj);
	printf("Hay un total de %d jugadores\n",longitud(lj));
	fflush(stdout);

	recorrer(lj);
	fflush(stdout);
	printf("Introduce un n�mero de goles: \n");
	fflush(stdout);
	scanf("%d",&num_goles);


	eliminar(&lj,num_goles);
	printf("--------------------------------------\n");
	recorrer(lj);
	printf("Hay un total de %d jugadores\n",longitud(lj));
	fflush(stdout);

	printf ("El jugador que m�s goles ha marcado es el que tiene ID: %d",maximo(lj));
	fflush(stdout);
	destruir (&lj);

	return 0;
}
