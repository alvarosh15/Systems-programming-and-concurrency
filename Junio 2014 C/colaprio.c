#include <stdio.h>
#include <stdlib.h>
#include "colaprio.h"

void insertar(TColaPrio *cp, unsigned int id, unsigned int prio) {
    TColaPrio nuevoNodo = malloc(sizeof(struct Nodo));
    nuevoNodo -> idproceso = id;
    nuevoNodo -> prioridad = prio;
    nuevoNodo -> sig = NULL;

    if(*cp == NULL) {
        *cp = nuevoNodo;
    } else {
        TColaPrio ptr = *cp;

        if(ptr -> prioridad > prio) { // Es el primero de la cola
            nuevoNodo -> sig = ptr;
            *cp = nuevoNodo;
        } else {
            while(ptr -> sig != NULL && ptr -> sig -> prioridad < prio) {
                ptr = ptr -> sig;
            }

            if(ptr -> sig != NULL) {
                if(ptr -> sig -> prioridad != prio) {
                    nuevoNodo -> sig = ptr -> sig;
                    ptr -> sig = nuevoNodo;
                } else {
                    ptr = ptr->sig;

					if (ptr->sig != NULL) {
						while (ptr->sig->prioridad == prio && ptr->sig != NULL) {
							ptr = ptr->sig;
						}
						nuevoNodo->sig = ptr->sig;
						ptr->sig = nuevoNodo;
					}
                }
            } else {
                ptr -> sig = nuevoNodo;
            } 
        }
    }
}

void Crear_Cola(char *nombre, TColaPrio *cp) {
    FILE * archivo = fopen(nombre, "rb");

    if(archivo == NULL) {
        perror("No se ha podido leer el archivo");
    } else {
        *cp = NULL;
        int num;
        int i = 0;
        int id, prio;

        fread(&num, sizeof(unsigned), 1, archivo);
        while (i < num) {
			fread(&id, sizeof(unsigned), 1, archivo);
			fread(&prio, sizeof(unsigned), 1, archivo);
			insertar(cp, id, prio);
			i++;
		}
		fclose(archivo);
    }
}

void Mostrar(TColaPrio cp) {
    if(cp == NULL) {
        printf("Lista vacia \n");
    } else {
        while(cp != NULL) {
            printf("identificador: %d, prioridad: %d\n", cp->idproceso, cp->prioridad);
            cp = cp -> sig;
        }
    }
}

void Destruir(TColaPrio *cp) {
    TColaPrio ptr;
    while(*cp != NULL) {
        ptr = *cp;
        *cp = (*cp)->sig;
        free(ptr);
    }
}

void Ejecutar_Max_Prio(TColaPrio *cp) {
    int max = 0;

    if(*cp != NULL) {
        TColaPrio ant = *cp;
        TColaPrio ptr = (*cp) -> sig;

        while(*cp != NULL) {
            if((*cp) -> prioridad > max) {
                max = (*cp) -> prioridad;
            }
            (*cp) = (*cp) -> sig;
        }
        *cp = ant;
        
		while (ptr != NULL && ptr->prioridad < max) {
			ant = ptr;
			ptr = ptr->sig;
		}

		if (ptr != NULL) {
			while (ptr != NULL) {
				ant->sig = ptr->sig;
				free(ptr);
				ptr = ant->sig;
			}
		}
    }
}

void Ejecutar(TColaPrio *cp, int prio) {
    if(*cp != NULL) {
        TColaPrio ant = *cp;
        TColaPrio ptr = (*cp) -> sig;

        while(ptr != NULL && ptr -> prioridad != prio) {
            ant = ant -> sig;
            ptr = ptr -> sig;
        }

        if(ptr != NULL) {
            while(ptr != NULL && ptr -> prioridad == prio) {
                ant -> sig = ptr -> sig;
                free(ptr);
                ptr = ant -> sig;
            }
        }
    }
}
