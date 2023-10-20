
public class Curso {

	private int conexiones = 0;
	private boolean maximoConexiones = false;

	private boolean grupoAvanzadoTrabajando = false;
	private boolean grupoAvanzadoHecho = false;
	private int numGrupoTerminado = 0;
	private boolean hanTerminado = false;
	private int numGrupo = 0;

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	
	
	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public synchronized void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte

		while(maximoConexiones) {
			wait();
		}	
		conexiones ++;
		if(conexiones == MAX_ALUMNOS_INI) {
			maximoConexiones = true;
		}
		//Mensaje a mostrar cuando el alumno pueda conectarse y cursar la parte de iniciacion
		System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion");
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public synchronized void finIniciacion(int id) throws InterruptedException{
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion");
		conexiones --;
		maximoConexiones = false;
		//Libera la conexion para que otro alumno pueda usarla
		notify();
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public synchronized void esperaPlazaAvanzado(int id) throws InterruptedException{
		//Espera a que no haya otro grupo realizando esta parte
		while(grupoAvanzadoTrabajando) {
			wait();
		}
		//Espera a que haya tres alumnos conectados
		numGrupo ++;
		if(numGrupo == ALUMNOS_AV) {
			grupoAvanzadoHecho = true;
			grupoAvanzadoTrabajando = true;
			notifyAll();
		}
		//Mensaje a mostrar si el alumno tiene que esperar al resto de miembros en el grupo
		System.out.println("		PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos");
		while(!grupoAvanzadoHecho) {
			wait();
		}
		
		//Mensaje a mostrar cuando el alumno pueda empezar a cursar la parte avanzada
		System.out.println("		PARTE AVANZADA: Hay " + ALUMNOS_AV + " alumnos. Alumno " + id + " empieza el proyecto");
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public synchronized void finAvanzado(int id) throws InterruptedException{
		//Espera a que los 3 alumnos terminen su parte avanzada
		numGrupoTerminado ++;
		if(numGrupoTerminado == ALUMNOS_AV) {
			hanTerminado = true;
			notifyAll();
		}
		System.out.println("		PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto");
		while(!hanTerminado) {
			wait();
		}
		//Mensaje a mostrar si el alumno tiene que esperar a que los otros miembros del grupo terminen

		//Mensaje a mostrar cuando los tres alumnos del grupo han terminado su parte
		numGrupoTerminado --;
		if(numGrupoTerminado == 0) {
			System.out.println("		PARTE AVANZADA: LOS " + ALUMNOS_AV + " ALUMNOS HAN TERMINADO EL CURSO");
			grupoAvanzadoTrabajando = false;
			numGrupo = 0;
			grupoAvanzadoHecho = false;
			numGrupoTerminado = 0;
			hanTerminado = false;
			notifyAll();
		}
	}
}
