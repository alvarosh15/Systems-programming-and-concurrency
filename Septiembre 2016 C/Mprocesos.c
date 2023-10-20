#include <stdio.h>
#include <stdlib.h>
#include "Mprocesos.h"

void Crear(LProc *lroundrobin) {
    lroundrobin = NULL;
}

void AnadirProceso(LProc *lroundrobin, int idproc) {
    LProc nuevoNodo = malloc(sizeof(struct Nodo));
    nuevoNodo -> proceso = idproc;
    nuevoNodo -> sig = *lroundrobin;
    if(*lroundrobin == NULL) {
        *lroundrobin = nuevoNodo;
    } else {
        LProc ptr = *lroundrobin;
        while(ptr -> sig != *lroundrobin) {
            ptr = ptr -> sig;
        }
        ptr -> sig = nuevoNodo;
    }
}

void EjecutarProcesos(LProc lroundrobin) {
        if(lroundrobin == NULL) {
            printf("Lista vacia \n");
        } else {
            LProc aux = lroundrobin;
            printf("\nLista: \n");
            do {
                printf(" %i ->", (aux->sig) -> proceso);
                aux = aux -> sig;
            } while (aux != lroundrobin);
        }
}

void EliminarProceso(int id, LProc *lista) {
    if(*lista != NULL) {
        LProc ptr = (*lista) -> sig;
        LProc ant = *lista;
        while(ptr -> proceso != id) {
            ant = ptr;
            ptr = ptr -> sig;
        }
        if(ant == ptr) {
            *lista = NULL;
            free(ptr);
        } else {
            ant -> sig = ptr -> sig;
            if (ptr == *lista) {
				*lista = ant;
			}
            free(ptr);
        }
    }
}

void EscribirFichero (char * nomf, LProc *lista) {
    FILE *archivo = fopen(nomf, 'w');
    if(archivo == NULL) {
        perror("No se ha podido escribir el fichero.");
    } else {
        if(*lista != NULL) {
            LProc ptr = (*lista);

            do {
                fwrite(&(ptr->proceso),sizeof(unsigned), 1, archivo);
                ptr = ptr -> sig;
            } while(ptr != *lista);
        }

		fclose(archivo);
    }
}