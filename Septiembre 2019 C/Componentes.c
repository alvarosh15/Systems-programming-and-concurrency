#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Componentes.h"

/*(0,5 puntos) La funcion Lista_Crear crea y devuelve una lista enlazada vacía de nodos de tipo Componente.*/
Lista Lista_Crear() {
    Lista lista = NULL;
    return lista;
}

/*(1 punto) La rutina Adquirir_Componente se encarga de recibir los datos 
de un nuevo componente (codigo y texto) que se introducen por teclado 
y devolverlos por los parametros pasados por referencia "codigo" y "texto". */
void Adquirir_Componente(long * codigo,char * texto) {
    printf("Introduce el codigo del componente: \n");
    scanf("%ld", codigo);
    printf("Introduce el texto del componente: \n");
    scanf("%s", texto);
}

/*(1 punto) La funcion Lista_Agregar toma como parametro 
un puntero a una lista, el codigo y el texto de un 
componente y anyade un nodo al final de la lista con estos datos. */
void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante) {
    Lista nuevoNodo = (Lista)malloc(sizeof(struct elemLista));
    nuevoNodo -> codigoComponente = codigo;
    strcpy(nuevoNodo -> textoFabricante, textoFabricante);

    if(*lista == NULL) {
        nuevoNodo -> sig = NULL,
        *lista = nuevoNodo;
    } else {
        Lista ptr = *lista;
        while(ptr -> sig != NULL) {
            ptr = ptr -> sig;
        }
        nuevoNodo -> sig = NULL;
        ptr -> sig = nuevoNodo;
    }
}

/*(1 punto) La funcion Lista_Imprimir se encarga de imprimir 
por pantalla la lista enlazada completa que se le pasa como parametro.*/
void Lista_Imprimir(Lista lista) {
    if(lista == NULL) {
        printf("Lista vacia \n");
    } else {
        while(lista != NULL) {
            printf("Codigo: %ld | Texto: %s \n", lista -> codigoComponente, lista -> textoFabricante);
            lista = lista -> sig;
        }
    }
}

/*(0,5 puntos) La rutina Lista_Vacia devuelve 1 
si la lista que se le pasa como parametro esta vacia y 0 si no lo esta.*/
int Lista_Vacia(Lista lista) {
    return lista == NULL;
}


/*(1 punto) Num_Elementos es una funcion a la que se 
le pasa una lista y devuelve el numero de elementos de dicha lista.*/
int Num_Elementos(Lista lista) {
    int num = 0;
    while(lista != NULL) {
        num ++;
        lista = lista -> sig;
    }
    return num;
}

/*(2 puntos) Lista_Extraer toma como parametro un puntero a 
una Lista y elimina el componente que se encuentra en su ultima posicion.*/
void Lista_Extraer(Lista *lista) {

    if(*lista != NULL) {
        Lista ant = NULL;
        Lista ptr = *lista;
        if((*lista )-> sig == NULL) {
            free(*lista);
        } else {
            while(ptr -> sig != NULL) {
                ant = ptr;
                ptr = ptr -> sig;
            }
            ant -> sig = NULL;
            free(ptr);
        }
    }
}

/*(1 punto) Lista_Vaciar es una funcion que toma como 
parametro un puntero a una Lista y extrae todos sus Componentes.*/
void Lista_Vaciar(Lista *lista) {
    Lista ptr = *lista;
    while(*lista != NULL) {
        ptr = *lista;
        *lista = (*lista) -> sig;
        free(ptr);
    }
}

/*(2 puntos) La funcion Lista_Salvar se encarga de guardar en el fichero binario "examen.dat" la 
lista enlazada completa que se le pasa como parametro.
Para cada nodo de la lista, debe almacenarse en el fichero el código y el texto de 
la componente correspondiente.*/
void Lista_Salvar(Lista lista) {
    FILE *archivo = fopen("examen.dat", "wb");

    if(archivo == NULL) {
        perror("No se ha podido abrir el fichero");
    } else {
		while (lista != NULL) {
			fwrite(&(lista->codigoComponente), sizeof(long), 1, archivo);
			fwrite(lista->textoFabricante, sizeof(char*), 1, archivo);
			lista = lista->sig;
		}
		fclose(archivo);
    }
}