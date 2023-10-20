#ifndef __COLAPRIO__
#define __COLAPRIO__

// Definición del tipo ColaPrio

typedef struct Nodo *TColaPrio;
struct Nodo{
	unsigned int idproceso;
	unsigned int prioridad;
	TColaPrio sig;
};

void Crear_Cola(char *nombre, TColaPrio *cp);
void Mostrar(TColaPrio cp);
void Destruir(TColaPrio *cp);
void Ejecutar_Max_Prio(TColaPrio *cp);
void Ejecutar(TColaPrio *cp, int prio);

#endif