#ifndef CIFRADO_H_
#define CIFRADO_H_

typedef struct TBox *TCifrado;

#define CAMBIA_BIT_POS_0 0
#define CAMBIA_BIT_POS_7 1
struct TBox {
  unsigned char esSBox;      //verdadero si es una SumaBox, falso si es una XORBox
  unsigned char bitACambiar; //valor para indicar si en una XORBox se
                             //cambia el valor del primer o del ultimo bit,
                             //segun las constantes indicadas arriba
  unsigned char valorASumar; //en una SumaBox: valor a sumar
  struct TBox *sig;
};


/* (0.5 puntos) funcion necesaria para crear un esquema de cifrado vacio, sin nodos*/
void crearEsquemaDeCifrado (TCifrado *cf);

/* (3 puntos) funcion que pone un nodo al final de un esquema de cifrado, si es posible.
 * Se debe devolver en el ultimo parametro un valor logico que sea verdadero si ha sido posible
 * realizar la operacion. No se debe suponer que el valor de box.sig es valido*/
void insertarBox (TCifrado * cf, struct TBox box, unsigned char *ok);

/* (1.5 puntos) funcion que dado un nodo y un valor, devuelve
 * el resultado de aplicar dicho nodo a dicho valor. Deberas
 * de tener en cuenta si el nodo es una SumaBox o una XORBox.
 * En el ultimo caso, necesitaras usar operadores logicos a
 * nivel de bit, como &, |, ^ o bien ~, asi como probablemente
 * usar constantes  numericas. */
unsigned char aplicarBox (struct TBox box, unsigned char valor);

/* (1.5 puntos) funcion que toma un esquema de cifrado y un valor,
 * y devuelve el resultado de aplicar dicho esquema de cifrado a
 * dicho valor, segun el metodo descrito anteriormente.*/
unsigned char aplicarEsquemaDeCifrado(TCifrado cf, unsigned char valor);

/* (2.5 puntos) funcion que toma un nombre de fichero, en el que se
 *  escribiran en modo binario los datos correspondientes al esquema
 *  de cifrado que se pasa como parametro, de modo que el al final el
 *  fichero unicamente contenga dichos datos. Si no se puede abrir el
 *  fichero, se debe de mostrar un mensaje de error por pantalla.*/
void escribirAFichero(char *nm, TCifrado cf);

/* (1.0 puntos) funcion que destruye un esquema de cifrado y libera la memoria que ocupa*/
void destruirEsquemaDeCifrado (TCifrado *cf);



#endif /* CIFRADO_H_ */
