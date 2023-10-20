#include <stdio.h>
#include <stdlib.h>
#include "Sistema.h"
#include <string.h>

//Crea una lista vacia
void Crear (LSistema  *ls) {
    *ls = NULL;
}


//Inserta un proceso por orden de llegada.
void InsertarProceso (LSistema *ls, int numproc) {

    LSistema nuevoNodo = malloc(sizeof(struct Nodo));
    nuevoNodo -> num = numproc;
    nuevoNodo -> hebra = NULL;
    nuevoNodo -> sig = NULL;

    if(*ls == NULL) { 
        *ls = nuevoNodo;
    } else {
        LSistema ptr = *ls;
        while(ptr -> sig != NULL) {
             ptr = ptr -> sig;
        }
        ptr -> sig = nuevoNodo;
    }
}

//Inserta una hebra en el proceso numproc teniendo en cuenta el orden de prioridad (mayor a menor)
void InsertarHebra (LSistema *ls, int numproc, char *idhebra, int priohebra) {

    if(*ls != NULL) {
        LSistema ptr = *ls;
        while(ptr != NULL && ptr -> num != numproc) {
            ptr = ptr -> sig;
        }
        if(ptr != NULL) {
            Hebra *hebra = malloc(sizeof(struct hebra));
            strcpy(hebra -> nombre, idhebra);
            hebra -> prio = priohebra;
            hebra -> sig = NULL;
            if(ptr -> hebra == NULL) {
                ptr -> hebra = hebra;
            } else {
                Hebra *ant = ptr -> hebra;
                if(ant->prio < hebra->prio) {
                    hebra->sig = ant;
					ptr->hebra = hebra;
                } else {
                    while (ant->sig != NULL && ant->sig->prio > priohebra) {
						ant = ant->sig;
					}
					hebra->sig = ant->sig;
					ant->sig = hebra;
                }
            }
        }
    }
}

//Muestra el contenido del sistema
void Mostrar (LSistema ls) {
	if (ls != NULL) {
		LSistema ptr = ls;

		while (ptr != NULL) {

			if (ptr->hebra == NULL) {	//no tiene hebra, imprime proceso
				printf("dato: %d\n", ptr->num);
				ptr = ptr->sig;

			} else {	//si tiene hebra, imprime proceso y hebra
				printf("dato: %d\n", ptr->num);	//imprime proceso

				Hebra *hebra = ptr->hebra;

				while (hebra != NULL) {		//imprime todas hebras
					printf("\thebra: %s, prioridad : %d \n", hebra->nombre,
							hebra->prio);
					hebra = hebra->sig;
				}
				ptr = ptr->sig;
			}
		}

	} else {
		printf("Esta vac�a \n");
	}
}

//Elimina del sistema el proceso con número numproc liberando la memoria de éste y de sus hebras.
void EliminarProc (LSistema *ls, int numproc) {
    if(*ls != NULL) {
        LSistema ptr = (*ls) -> sig;
        LSistema ant = *ls;

        while(ptr != NULL && ptr->num != numproc) {
            ant = ptr;
            ptr = ptr -> sig;
        }

        if(ptr != NULL) {
            ant -> sig = ptr -> sig;

            while(ptr -> hebra != NULL) {
                Hebra *hebra;
                hebra = ptr -> hebra;
                ptr -> hebra = ptr -> hebra -> sig;
                free(hebra);
            }
            free(ptr);
        }
    } 
}

//Destruye toda la estructura liberando su memoria
void Destruir (LSistema *ls) {

    while(*ls != NULL) {

        LSistema ptr = *ls;

        if(ptr -> hebra == NULL) {
            *ls = (*ls) -> sig;
            free(ptr);
        } else {
            while(ptr -> hebra != NULL) {
                Hebra * hebra;
                hebra = ptr -> hebra;
                ptr -> hebra = ptr -> hebra -> sig;
                free(hebra);
            }
            *ls = ptr -> sig;
            free(ptr);
        }
    }
}

    