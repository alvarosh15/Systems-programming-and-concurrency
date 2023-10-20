import java.util.concurrent.Semaphore;

public class Curso {

	private int conexiones = 0;
	private Semaphore mutex = new Semaphore(1);
	private Semaphore esperaConexion = new Semaphore(1);

	private int numGrupo = 0;
	private int numAcaba = 0;

	private Semaphore mutexGrupo = new Semaphore(1);
	private Semaphore hayUnGrupoTrabajando = new Semaphore(1);
	private Semaphore grupo = new Semaphore(0);

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	
	
	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte
		
		esperaConexion.acquire();
		mutex.acquire();
		conexiones ++;
		//Mensaje a mostrar cuando el alumno pueda conectarse y cursar la parte de iniciacion
		System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion");

		if(conexiones < MAX_ALUMNOS_INI) {
			esperaConexion.release();
		}

		mutex.release();
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public void finIniciacion(int id) throws InterruptedException{
		mutex.acquire();
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion");

		conexiones --;

		//Libera la conexion para que otro alumno pueda usarla
		if(conexiones == MAX_ALUMNOS_INI - 1) { // Le quito 1 porque he hecho conexiones -- antes.
			esperaConexion.release();
		}
		
		mutex.release();
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public void esperaPlazaAvanzado(int id) throws InterruptedException{
		//Espera a que no haya otro grupo realizando esta parte

		hayUnGrupoTrabajando.acquire();

		//Espera a que haya tres alumnos conectados

		mutexGrupo.acquire();
	
		numGrupo ++;
		
		//Mensaje a mostrar si el alumno tiene que esperar al resto de miembros en el grupo
		System.out.println("PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos");
		
		if(numGrupo < 3) {
			mutexGrupo.release();
			hayUnGrupoTrabajando.release();
			grupo.acquire();
			mutexGrupo.acquire();
		} else {
			grupo.release();
			grupo.release();
		}

		//Mensaje a mostrar cuando el alumno pueda empezar a cursar la parte avanzada
		System.out.println("PARTE AVANZADA: Hay " + ALUMNOS_AV + " alumnos. Alumno " + id + " empieza el proyecto");
		mutexGrupo.release();
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public void finAvanzado(int id) throws InterruptedException{
		//Espera a que los 3 alumnos terminen su parte avanzada
		mutexGrupo.acquire();
		numAcaba ++;
		System.out.println("PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto");
		if(numAcaba < 3) {
			mutexGrupo.release();
			grupo.acquire();
			mutexGrupo.acquire();
		} else {
			grupo.release();
			grupo.release();
		}

		numAcaba --;

		if(numAcaba == 0) {
			System.out.println("PARTE AVANZADA: LOS " + ALUMNOS_AV + " ALUMNOS HAN TERMINADO EL CURSO");
			numGrupo = 0;
			hayUnGrupoTrabajando.release();
		}

		//Mensaje a mostrar si el alumno tiene que esperar a que los otros miembros del grupo terminen

		//Mensaje a mostrar cuando los tres alumnos del grupo han terminado su parte
		mutexGrupo.release();
	}
}
