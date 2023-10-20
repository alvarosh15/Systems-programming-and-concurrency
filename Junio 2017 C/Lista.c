#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializa la lista de puntos creando una lista vacía
 *
 */
void crearLista(TLista *lista) {
    *lista = NULL;
}


/**
 * Inserta el punto de forma ordenada (por el valor de la abscisa x)
 * en la lista siempre que no esté repetida la abscisa.
 *  En ok, se devolverá un 1 si se ha podido insertar, y  0 en caso contrario.
 *  Nota: utiliza una función auxiliar para saber
 *   si ya hay un punto en la lista con la misma abscisa punto.x
 *
 */
void insertarPunto(TLista *lista, struct Punto punto, int * ok) {
    TLista nuevoNodo = (TLista)malloc(sizeof(struct Nodo));
    nuevoNodo -> punto = punto;
    nuevoNodo -> sig = NULL;

    if(*lista == NULL) {
        *lista = nuevoNodo;
        *ok = 1;
    } else {
        int esta = 0;
        TLista ptr = *lista;
        while(ptr -> sig != NULL && esta == 0) {
            if(ptr -> punto.x == punto.x) {
                esta = 1;
            }
            ptr = ptr -> sig;
        }
        ptr = *lista;
        if(esta == 0) {
            if(ptr -> punto.x > nuevoNodo -> punto.x) {
                nuevoNodo -> sig = ptr;
                *lista = nuevoNodo;
                *ok = 1;
            } else {
                while(ptr -> sig != NULL && ptr -> punto.x < nuevoNodo -> punto.x) {
                    ptr = ptr -> sig;
                }
                nuevoNodo -> sig = ptr -> sig;
                ptr -> sig = nuevoNodo;
                *ok = 1;
            }
        } else {
            *ok =  1;
        }
    }
}


/*
 * Elimina de la lista el punto con abscisa x de la lista.
 * En ok devolverá un 1 si se ha podido eliminar,
 * y un 0 si no hay ningún punto en la lista con abscisa x
 *
 */
void eliminarPunto(TLista *lista,float x,int* ok) {
    if(*lista != NULL) {
        if((*lista) -> punto.x == x) {
            *lista = (*lista) -> sig;
            free(*lista);
            *ok = 1;
        } else {
            TLista ant = *lista;
            TLista ptr = (*lista) -> sig;
            while(ptr != NULL && ptr -> punto.x != x) {
                ant = ptr;
                ptr = ptr -> sig;
            }
            if(ptr != NULL) {
                ant -> sig = ptr -> sig;
                free(ptr);
                *ok = 1;
            }
        }
    } else {
        *ok = 0;
    }
}


 /**
 * Muestra en pantalla el listado de puntos
 */
void mostrarLista(TLista lista) {
    if(lista == NULL) {
        printf("Lista vacia.");
    } else {
        printf("\n Lista: \n");
        while(lista != NULL) {
            printf("X: %f Y: %f \n", lista->punto.x, lista->punto.y);
            lista = lista -> sig;
        }
    }
}

/**
 * Destruye la lista de puntos, liberando todos los nodos de la memoria.
 */
void destruir(TLista *lista) {
    TLista ptr;
    while(*lista != NULL) {
        ptr = *lista;
        *lista = (*lista) -> sig;
        free(ptr);
    }
}

/*
 * Lee el contenido del archivo binario de nombre nFichero,
 * que contiene una secuencia de puntos de una función polinómica,
 *  y lo inserta en la lista.
 *
 */
void leePuntos(TLista *lista,char * nFichero) {
    int ok;
    FILE *archivo = fopen(nFichero, "rb");

    if(archivo != NULL) {
        perror("No se ha podido abrir el fichero.");
    } else { 
        struct Punto p;
        while(fread(&p, sizeof(struct Punto), 1, archivo) == 1) {
            insertarPunto(lista, p, &ok);
        }
        fclose(archivo);
    }
}
