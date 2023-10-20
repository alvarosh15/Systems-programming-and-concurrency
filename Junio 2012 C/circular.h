typedef struct circular *LProc;

struct circular
{
    int pid;
    LProc sig;
};

void Crear(LProc *lista);

void AnyadirProceso(LProc *lista, int idproc);

void MostrarLista(LProc lista);

void EjecutarProceso(LProc *lista);