#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "circular.h"

void Crear(LProc *lista) {
    *lista = NULL;
}

void AnyadirProceso(LProc *lista, int idproc)
{
    LProc newProcess = malloc(sizeof(struct circular));
    newProcess->pid = idproc;   
    if ((*lista) == NULL)
    {
        *lista = newProcess;
        newProcess->sig = *lista;
    }
    else
    {
        LProc aux = *lista;
        while ((aux->sig) != (*lista))
        {
            aux = aux->sig;
        }

        aux->sig = newProcess;
        newProcess->sig = *lista;
    }
}

void MostrarLista(LProc lista) {
        if(lista == NULL) {
            printf("Lista vacia \n");
        } else {
            LProc aux = lista;
            printf("\nLista: \n");
            do {
                printf(" %i ->", (aux->sig) -> pid);
                aux = aux -> sig;
            } while (aux != lista);
        }
}

void EjecutarProceso(LProc *lista) {
    if (*lista == NULL){
        perror("No se puede eliminar ningún proceso de una lista vacia.");
    } else if ((*lista)->sig == (*lista)){
        *lista = NULL;
        perror("Se ha eliminado la lista completamente");
    } else {
        LProc aux = (*lista);
        LProc ptr = (*lista);
        while (aux->sig != *lista){
            aux = aux->sig;
        }
        *lista = (*lista)->sig;
        aux->sig = (*lista);
        free(ptr);
    }
}