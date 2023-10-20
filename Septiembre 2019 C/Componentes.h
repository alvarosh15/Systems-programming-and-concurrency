/*
 ============================================================================
 Nombre y Apellidos:
 DNI:
 Titulación y Grupo:
 Ordenador:
 ============================================================================
 */

#ifndef COMPONENTES_H
#define COMPONENTES_H_
#include <stdio.h>
#include <stdlib.h>

#define MAX_CADENA 33

/*
-----------DEFINICION DE ALIAS DE TIPOS-----------------
*/

/*
Esta sera la estructura principal de los nodos de nuestra lista
*/

typedef struct elemLista {
	long codigoComponente;
	char textoFabricante[MAX_CADENA];
	struct elemLista * sig;
} Componente;

/*
Definimos el tipo lista como un puntero al tipo Componente que constituye el tipo de los nodos de nuestra lista
*/
typedef Componente * Lista;


/*
-----------------PROTOTIPOS DE RUTINAS------------------
*/


/*
La rutina Lista_Vacia devuelve 1 si la lista que se le pasa
como parametro esta vacia y 0 si no lo esta.
*/
int Lista_Vacia(Lista lista);

/*Num_Elementos es una funcion a la que se le pasa un puntero a una lista 
y devuelve el numero de elementos de dicha lista.
*/
int Num_Elementos(Lista  lista);

/*
La rutina Adquirir_Componente se encarga de recibir los datos de un nuevo 
componente (codigo y texto) que se le introducen por teclado y devolverlos 
por los parametros pasados por referencia "codigo" y "texto".
*/
 void Adquirir_Componente(long *codigo,char *texto);

/*
La funcion Lista_Imprimir se encarga de imprimir por pantalla la lista 
enlazada completa que se le pasa como parametro.
*/
void Lista_Imprimir( Lista lista);

/*
La funcion Lista_Salvar se encarga de guardar en el fichero binario 
"examen.dat" la lista enlazada completa que se le pasa como parametro. 
Para cada nodo de la lista, debe almacenarse en el fichero
el código y el texto de la componente correspondiente.
*/
void Lista_Salvar( Lista  lista);


/*
La funcion Lista_Crear crea una lista enlazada vacia
de nodos de tipo Componente.
*/
Lista Lista_Crear();

/*
La funcion Lista_Agregar toma como parametro un puntero a una lista,
el código y el texto de un componente y  anyade un nodo al final de 
la lista con estos datos.
*/
void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante);

/*
Lista_Extraer toma como parametro un puntero a una Lista y elimina el
Componente que se encuentra en su ultima posicion.
*/
void Lista_Extraer(Lista *lista);

/*
Lista_Vaciar es una funcion que toma como parametro un puntero a una Lista
y elimina todos sus Componentes.
*/
void Lista_Vaciar(Lista *lista);

#endif /* COMPONENTES_H_ */

// Fin fichero
// ===========
