
// Definir aqu�
// TListaJugadores;
typedef struct Nodo * TListaJugadores;

struct Nodo{
	unsigned int nJug;
	unsigned int nGoles;
	TListaJugadores sig;
};

//crea una lista vac�a (sin ning�n nodo)
void crear(TListaJugadores *lc);

//inserta un nuevo jugador en la lista de jugadores, poniendo 1 en el n�mero de goles marcados.
//Si ya existe a�ade 1 al n�mero de goles marcados.
void insertar(TListaJugadores *lj,unsigned int id);

//recorre la lista circular escribiendo los identificadores y los goles marcados
void recorrer(TListaJugadores lj);

//devuelve el n�mero de nodos de la lista
int longitud(TListaJugadores lj);

//Eliminar. Toma un n�mero de goles como par�metro y
//elimina todos los jugadores que hayan marcado menos que ese n�mero de goles
void eliminar(TListaJugadores *lj,unsigned int n);


// Devuelve el ID del m�ximo jugador. Si la lista est� vac�a devuelve 0. Si hay m�s de un jugador con el mismo n�mero de goles que el m�ximo devuelve el de mayor ID
// Hay que devolver el identificador, no el n�mero de goles que ha marcado
unsigned int maximo(TListaJugadores lj);

//Destruye la lista y libera la memoria)
void destruir(TListaJugadores *lj);


