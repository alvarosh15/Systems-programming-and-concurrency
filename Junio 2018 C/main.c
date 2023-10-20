#include "cifrado.h"

#include <stdio.h>

#define FICHERO1 "cifrado1.bin"
#define FICHERO2 "cifrado2.bin"

#define PUNTERO_BASURA (TCifrado)0x1234567890abcdef
#define VALOR_BASURA 123

#define ESSBOX 1
#define ESXBOX 0

int main() {
  TCifrado cf, vacio;
  unsigned char ok, entrada, salida;

  crearEsquemaDeCifrado(&cf);
  crearEsquemaDeCifrado(&vacio);

  insertarBox(&cf, (struct TBox){ESXBOX, CAMBIA_BIT_POS_0, VALOR_BASURA, PUNTERO_BASURA}, &ok);
  if (ok) {
      printf("Este primer nodo no deberia de haberse insertado correctamente.");
      
  }

  insertarBox(&cf, (struct TBox){ESSBOX, VALOR_BASURA, 0x8C, PUNTERO_BASURA}, &ok);
  if (!ok) {
      printf("El primer nodo no se ha insertado correctamente");
      return -1;
  }

  insertarBox(&cf, (struct TBox){ESXBOX, CAMBIA_BIT_POS_7, VALOR_BASURA, PUNTERO_BASURA}, &ok);
  if (!ok) {
      printf("El segundo nodo no se ha insertado correctamente");
      return -1;
  }

  insertarBox(&cf, (struct TBox){ESSBOX, VALOR_BASURA, 0x17, PUNTERO_BASURA}, &ok);
  if (!ok) {
      printf("El tercer nodo no se ha insertado correctamente");
      return -1;
  }

  insertarBox(&cf, (struct TBox){ESSBOX, VALOR_BASURA, 0x48, PUNTERO_BASURA}, &ok);
  if (ok) {
      printf("Este ultimo nodo no deberia de haberse insertado correctamente.");
  }

  entrada = 100;

  salida = aplicarEsquemaDeCifrado(cf, entrada);
  printf("El resultado de aplicar el esquema de cifrado construido al valor 0x%x es 0x%x\n\n", entrada, salida);

  salida = aplicarEsquemaDeCifrado(vacio, entrada);
  printf("El resultado de aplicar un esquema de cifrado vacio al valor 0x%x es 0x%x\n\n", entrada, salida);

  printf("Escribimos el esquema de cifrado construido en el fichero " FICHERO1 "\n\n");
  escribirAFichero(FICHERO1, cf);

  printf("Escribimos un esquema de cifrado vacio en el fichero " FICHERO2 "\n\n");
  escribirAFichero(FICHERO2, vacio);

  printf("Destruimos ambos esquemas de cifrado\n");
  destruirEsquemaDeCifrado(&cf);
  destruirEsquemaDeCifrado(&vacio);

  return 0;
}

