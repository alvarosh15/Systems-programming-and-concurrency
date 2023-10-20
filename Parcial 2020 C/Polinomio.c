#include "Polinomio.h"

/*Crea el polinomio 0 (es decir, un polinomio vacío).
*/
void polinomioCero(TPolinomio *p) {
	*p = NULL;
}

/*Devuelve el grado del polinomio, es decir, el mayor exponente de los
* monomios que no son nulos. En el ejemplo, el grado es 7.
*/
int grado(TPolinomio p) {
	int gradoMax = 0;

	while(p != NULL) {
		if(p -> exp > gradoMax) {
			gradoMax = p -> exp;
		}
		p = p -> sig;
	}

	return gradoMax;
}

/* Devuelve el coeficiente de exponente exp del polinomio p.
*/
int coeficiente(TPolinomio p,unsigned int exp) {
	int coef = 0;

	while(p != NULL) {
		if(p -> exp == exp) {
			coef = p -> coef;
		}
		p = p -> sig;
	}

	return coef;
}

/* Insertar el monomio con coeficiente coef, y exponente exp en el polinomio,
 * de manera que el polinomio quede ordenado.
 * Asegurarse que no se insertan monomios cuyo coeficiente sea 0 y
 * tampoco dos monomios con el mismo exponente.
 * Si al insertar un monomio ya hay otro con el mismo exponente
 * los coeficientes se sumarán. Se puede asumir que el valor del coeficiente coef a
 *  sumar siempre será un número natural (un entero no negativo)
*/
void insertar(TPolinomio *p,unsigned int coef,unsigned int exp) {
	if(coef != 0) {
		TPolinomio nuevoNodo = malloc(sizeof(struct TNodo));
		nuevoNodo -> coef = coef;
		nuevoNodo -> exp = exp;
		nuevoNodo -> sig = NULL;

		if(*p == NULL) {
			*p = nuevoNodo;
		} else {
			int esta = 0;
			TPolinomio ptr = *p;
			TPolinomio aux = *p;

			while(ptr != NULL && esta == 0) {
				if(ptr -> exp == exp) {
					ptr -> coef = (ptr -> coef) + coef;
					esta = 1;
				}
				ptr = ptr -> sig;
			}

			if(esta == 0) {
				if((*p) -> exp > exp) {
					nuevoNodo -> sig = *p;
					*p = nuevoNodo;
				} else {
					while(aux -> sig != NULL && exp > aux -> sig -> exp) {
						aux = aux -> sig;
					}
					nuevoNodo -> sig = aux -> sig;
					aux -> sig = nuevoNodo;
				}
			}
		}
	} 
}

/*Escribe por la pantalla el polinomio con un formato similar al siguiente:
* [(9,0)(5,1)(3,3)(2,5)(3,7)] para el polinomio ejemplo.
*/
void imprimir(TPolinomio p) {
	printf("\n[");
	while(p != NULL) {
		printf("(%i,%i)", p->coef, p->exp);
		p = p -> sig;
	}
	printf("]\n");
}


/* Elimina todos los monomios del polinomio haciendo
 * que el polinomio resultante sea el polinomio 0.
*/
void destruir(TPolinomio *p) {
	TPolinomio ptr;
	while(*p != NULL) {
		ptr = *p;
		*p = (*p) -> sig;
		free(ptr);
	}
}

/* Lee los coeficientes de un polinomio que están almacenados en
* un fichero de texto, y crean la lista de monomios p.
* Los coeficientes en el fichero de texto van de menor exponente a mayor exponente
* y son dígitos del 0 al 9.
* Por ejemplo, para el polinomio ejemplo el fichero de texto estaría compuesto por
* la secuencia de caracteres “95030203”. La conversión de un valor de tipo ‘char’
* que contenga un valor númerico (ej. char c = ‘2’) a su correspondiente valor
* entero (int valor), se puede hacer de la siguiente forma: valor = c – ‘0’.
*/
void crearDeFichero(TPolinomio *p, char *nombre) {
	FILE *archivo = fopen(nombre, 'wb');

	if(archivo == NULL) {
		perror("No se ha podido abrir el fichero");
	} else {
		char coef;
		unsigned int c;
		unsigned int i = 0;
		while(fscanf(archivo, "%c", &coef) == 1) {
			c = coef -'0';
			insertar(p,c,i);
			i ++;
		}
		fclose(archivo);
	}
}

