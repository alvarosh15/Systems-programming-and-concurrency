import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Curso {

	private int conexiones = 0;
	private int grupo = 0;
	private int grupoHanAcabado = 0;
	private boolean finalizado = false;
	private Lock l = new ReentrantLock();
	private Condition esperaConexion = l.newCondition();
	private Condition esperaQueAcaben = l.newCondition();
	private Condition esperaGrupo = l.newCondition();
	private Condition esperaQueElRestoAcabe = l.newCondition();

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	
	
	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public void esperaPlazaIniciacion(int id) throws InterruptedException{
		l.lock();
		try {
			//Espera si ya hay 10 alumnos cursando esta parte
			while(conexiones == MAX_ALUMNOS_INI) {
				esperaConexion.await();
			}
			conexiones ++;
			//Mensaje a mostrar cuando el alumno pueda conectarse y cursar la parte de iniciacion
			System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion");
		} finally {
			l.unlock();
		}
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public void finIniciacion(int id) throws InterruptedException{
		l.lock();
		try {
			//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
			System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion");
			conexiones --;
			
			//Libera la conexion para que otro alumno pueda usarla
			esperaConexion.signal();
		} finally {
			l.unlock();
		}
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public void esperaPlazaAvanzado(int id) throws InterruptedException{
		l.lock();
		try {
			//Espera a que no haya otro grupo realizando esta parte
			while(grupo == ALUMNOS_AV) {
				esperaQueAcaben.await();
			}

			grupo ++;
			if(grupo == ALUMNOS_AV) {
				esperaGrupo.signalAll();
			}
			//Espera a que haya tres alumnos conectados
			//Mensaje a mostrar si el alumno tiene que esperar al resto de miembros en el grupo
			System.out.println("		PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos");
			while(grupo < ALUMNOS_AV) {
				esperaGrupo.await();
			}
	
			//Mensaje a mostrar cuando el alumno pueda empezar a cursar la parte avanzada
			System.out.println("		PARTE AVANZADA: Hay " + ALUMNOS_AV + " alumnos. Alumno " + id + " empieza el proyecto");
	
		} finally {
			l.unlock();
		}
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public void finAvanzado(int id) throws InterruptedException{
		l.lock();
		try {
			//Espera a que los 3 alumnos terminen su parte avanzada
			grupoHanAcabado ++;
			if(grupoHanAcabado == ALUMNOS_AV) {
				finalizado = true;
				esperaQueElRestoAcabe.signalAll();
			}
			//Mensaje a mostrar si el alumno tiene que esperar a que los otros miembros del grupo terminen
			System.out.println("		PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto");
			while(!finalizado) {
				esperaQueElRestoAcabe.await();
			}
			grupoHanAcabado --;
			if(grupoHanAcabado == 0) {
				//Mensaje a mostrar cuando los tres alumnos del grupo han terminado su parte
				System.out.println("		PARTE AVANZADA: LOS " + ALUMNOS_AV + " ALUMNOS HAN TERMINADO EL CURSO");
				grupo = 0;
				grupoHanAcabado = 0;
				finalizado = false;
				esperaQueAcaben.signalAll();
			}
		} finally {
			l.unlock();
		}
	}
}
