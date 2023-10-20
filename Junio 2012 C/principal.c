#include <assert.h>
#include <stdlib.h>
#include "circular.h"

int main(int argc, char const *argv[])
{
    LProc lista;

    Crear(&lista);
    assert(lista == NULL);

    MostrarLista(lista);

    EjecutarProceso(&lista);
    assert(lista == NULL);

    AnyadirProceso(&lista, 1);
    assert(lista->pid == 1);
    assert(lista->sig == lista);

    EjecutarProceso(&lista);
    assert(lista == NULL);

    AnyadirProceso(&lista, 1);
    AnyadirProceso(&lista, 3);
    AnyadirProceso(&lista, 5);
    assert(lista->pid == 1);
    assert(lista->sig->pid == 3);
    assert(lista->sig->sig->pid == 5);
    assert(lista->sig->sig->sig == lista);
    MostrarLista(lista); // 1 3 5

    EjecutarProceso(&lista);
    EjecutarProceso(&lista);
    assert(lista->pid == 5);
    assert(lista->sig == lista);

    MostrarLista(lista); // 5

    return 0;
}
