#include "cifrado.h"
#include <stdio.h>
#include <stdlib.h>

/* (0.5 puntos) funcion necesaria para crear un esquema de cifrado vacio, sin nodos*/
void crearEsquemaDeCifrado (TCifrado *cf) {
    *cf = NULL;
}

/* (3 puntos) funcion que pone un nodo al final de un esquema de cifrado, si es posible.
 * Se debe devolver en el ultimo parametro un valor logico que sea verdadero si ha sido posible
 * realizar la operacion. No se debe suponer que el valor de box.sig es valido*/
void insertarBox (TCifrado * cf, struct TBox box, unsigned char *ok) {

    TCifrado nuevoNodo = (TCifrado)malloc(sizeof(struct TBox));
    nuevoNodo -> bitACambiar = box.bitACambiar;
    nuevoNodo -> esSBox = box.esSBox;
    nuevoNodo -> valorASumar = box.valorASumar;
    nuevoNodo -> sig = NULL;

    if(*cf == NULL) {
        *cf = nuevoNodo;
        *ok = 1;
    } else {
        TCifrado ptr = *cf;
        while(ptr -> sig != NULL) {
            ptr = ptr -> sig;
        }
        ptr -> sig = nuevoNodo;
    }
}

/* (1.5 puntos) funcion que dado un nodo y un valor, devuelve
 * el resultado de aplicar dicho nodo a dicho valor. Deberas
 * de tener en cuenta si el nodo es una SumaBox o una XORBox.
 * En el ultimo caso, necesitaras usar operadores logicos a
 * nivel de bit, como &, |, ^ o bien ~, asi como probablemente
 * usar constantes  numericas. */

unsigned char cambiarBit0(unsigned char valor) {
	if ((valor & 1) == 1)
		return (valor & ~1);
	else
		return (valor | 1);
}

unsigned char cambiarBit7(unsigned char valor) {
	if (((valor & (1 << 7)) >> 7) == 1)
		return (valor & (~(1 << 7)));
	else
		return (valor | (1 << 7));
}

unsigned char aplicarBox (struct TBox box, unsigned char valor) {
    if(box.esSBox) {
        valor = valor + box.valorASumar;
    } else {
        if (box.bitACambiar == 1) {
			valor = cambiarBit0(valor); // ^ 1 (en formato byte);
		} else {
			valor = cambiarBit0(valor); // ^ 7 (en formato byte);
		}
    }
    return valor;
}
/* (1.5 puntos) funcion que toma un esquema de cifrado y un valor,
 * y devuelve el resultado de aplicar dicho esquema de cifrado a
 * dicho valor, segun el metodo descrito anteriormente.*/
unsigned char aplicarEsquemaDeCifrado(TCifrado cf, unsigned char valor) {
    struct TBox box;
    while (cf != NULL) {
        box.bitACambiar = cf->bitACambiar;
		box.esSBox = cf->esSBox;
		box.valorASumar = cf->valorASumar;
        valor = aplicarBox(box, valor);
        cf = cf -> sig;
    }
    return valor;
}

/* (2.5 puntos) funcion que toma un nombre de fichero, en el que se
 *  escribiran en modo binario los datos correspondientes al esquema
 *  de cifrado que se pasa como parametro, de modo que el al final el
 *  fichero unicamente contenga dichos datos. Si no se puede abrir el
 *  fichero, se debe de mostrar un mensaje de error por pantalla.*/
void escribirAFichero(char *nm, TCifrado cf) {
    FILE *archivo = fopen(nm, "wb");

    if(archivo == NULL) {
        perror("No se ha podido abrir el archivo.");
    } else {
        while(cf != NULL) {
            fwrite(&(cf->esSBox), sizeof(unsigned), 1, archivo);
            fwrite(&(cf->bitACambiar), sizeof(unsigned), 1, archivo);
            fwrite(&(cf->valorASumar), sizeof(unsigned), 1, archivo);
            cf = cf -> sig;
        }
        fclose(archivo);
    }
}

/* (1.0 puntos) funcion que destruye un esquema de cifrado y libera la memoria que ocupa*/
void destruirEsquemaDeCifrado (TCifrado *cf) {
    TCifrado ptr;
    while(*cf != NULL) {
        ptr = *cf;
        *cf = (*cf) -> sig;
        free(ptr);
    }
}