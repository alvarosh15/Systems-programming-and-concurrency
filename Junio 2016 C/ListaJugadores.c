#include "ListaJugadores.h"
#include <stdio.h>
#include <stdlib.h>

//crea una lista vac�a (sin ning�n nodo)
void crear(TListaJugadores *lc) {
    *lc = NULL;
}

//inserta un nuevo jugador en la lista de jugadores, poniendo 1 en el n�mero de goles marcados.
//Si ya existe a�ade 1 al n�mero de goles marcados.
void insertar(TListaJugadores *lj,unsigned int id) {

    int esta = 0;
    TListaJugadores ptr = *lj;
    while(ptr != NULL && esta == 0) {
        if(ptr -> nJug == id) {
            ptr -> nGoles ++;
            esta = 1;
        }
        ptr = ptr -> sig;
    }
    if(esta == 0) {
        TListaJugadores nuevoNodo = malloc(sizeof(struct Nodo));
        nuevoNodo -> nJug = id;
        nuevoNodo -> nGoles = 1;
        nuevoNodo -> sig = NULL;
        if(*lj == NULL) {
            nuevoNodo -> nGoles = 1;
            *lj = nuevoNodo;
        } else if (nuevoNodo -> nJug < (*lj) -> nJug){
            nuevoNodo -> sig = *lj;
            *lj = nuevoNodo;
        } else {
            TListaJugadores ant = (*lj);
            ptr = (*lj) -> sig;
            while(ptr != NULL && ptr -> nJug > nuevoNodo -> nJug) {
                ant = ant -> sig;
                ptr = ptr -> sig;
            }
            nuevoNodo -> sig = ptr;
            ant -> sig = nuevoNodo;
        }
    }

}

//recorre la lista circular escribiendo los identificadores y los goles marcados
void recorrer(TListaJugadores lj) {
    if(lj == NULL) {
        printf("Lista vacia \n");
    } else {
        while(lj != NULL) {
            printf("Numero de jugador: %i Numero de goles: %i \n", lj -> nJug, lj ->nGoles);
            lj = lj -> sig;
        }
    }
}

//devuelve el n�mero de nodos de la lista
int longitud(TListaJugadores lj) {
    int count = 0;
    while(lj != NULL) {
        count ++;
        lj = lj -> sig;
    }
    return count;
}

//Eliminar. Toma un n�mero de goles como par�metro y
//elimina todos los jugadores que hayan marcado menos que ese n�mero de goles
void eliminar(TListaJugadores *lj,unsigned int n) {
    TListaJugadores ant = NULL;
    TListaJugadores ptr = *lj;
    while(ptr != NULL) {
        if(ptr -> nGoles < n) {
            if(ant == NULL) {
                *lj = ptr -> sig;
                free(ptr);
                ptr = *lj;
            } else {
                ant -> sig = ptr -> sig;
                free(ptr);
                ptr = ant -> sig;
            }
        } else {
            ant = ptr;
            ptr = ptr -> sig;
        }
    }
}


// Devuelve el ID del m�ximo jugador. Si la lista est� vac�a devuelve 0. Si hay m�s de un jugador con el mismo n�mero de goles que el m�ximo devuelve el de mayor ID
// Hay que devolver el identificador, no el n�mero de goles que ha marcado
unsigned int maximo(TListaJugadores lj) {
    int count = 0;
    int maxId;

    if(lj == NULL) {
        maxId = 0;
    } else {
        TListaJugadores ptr = lj;
        while(ptr != NULL) {
            if(ptr -> nGoles > count) {
                count = ptr -> nGoles;
                maxId = ptr -> nJug;
            } else if (ptr -> nGoles == count){
                if(ptr -> nJug > maxId) {
                  maxId = ptr -> nJug;
                }
            }
            ptr = ptr -> sig;
        }
    }
    return maxId;
}

//Destruye la lista y libera la memoria)
void destruir(TListaJugadores *lj) {
    TListaJugadores ptr;
    while(*lj != NULL) {
        ptr = *lj;
        *lj = (*lj) -> sig;
        free(ptr);
    }
}


