
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Concurso {

	private int tiradas1 = 0;
	private int tiradas2 = 0;
	private int caras1 = 0;
	private int caras2 = 0;
	private int victorias1 = 0;
	private int victorias2 = 0;
	private int partida = 1;
	private Lock l = new ReentrantLock();
	private Condition jugador1 = l.newCondition();
	private Condition jugador2 = l.newCondition();
	
	public void tirarMoneda(int id,boolean cara) throws InterruptedException {

		l.lock();
		try {
			if(cara) {
				if(id == 1) {
					caras1 ++;
				} else {
					caras2 ++;
					
				}
			}
		
			if(id == 1) {
				tiradas1 ++;
				if(tiradas1 == 10 && tiradas2 < 10) {
					jugador1.await();
				} else if(tiradas1 == 10 && tiradas2 == 10) {
					if(caras1 > caras2) {
						victorias1 ++;
						System.out.println("Juego " + partida + ": Ha ganado la partida el jugador 1 con " + caras1);
					} else if (caras2 > caras1) {
						victorias2 ++;
						System.out.println("Juego " + partida + ": Ha ganado la partida el jugador 2 con " + caras2);
					} else {
						System.out.println("Juego " + partida + ": El juego ha empatado");
					}
					partida ++;
					tiradas1 = 0;
					tiradas2 = 0;
					caras1 = 0;
					caras2 = 0;
					jugador2.signal();
				}
			} else {
				tiradas2 ++;
				if(tiradas2 == 10 && tiradas1 < 10) {
					jugador2.await();
				} else if(tiradas1 == 10 && tiradas2 == 10) {
					if(caras1 > caras2) {
						victorias1 ++;
						System.out.println("Juego " + partida + ": Ha ganado la partida el jugador 1 con " + caras1);
					} else {
						victorias2 ++;
						System.out.println("Juego " + partida + ": Ha ganado la partida el jugador 2 con " + caras2);
					}
					partida ++;
					tiradas1 = 0;
					tiradas2 = 0;
					caras1 = 0;
					caras2 = 0;
					jugador1.signal();
				}
			}
		} finally {
			l.unlock();
		}
		
	}	
	
	public boolean concursoTerminado() {
		l.lock();
		try {
			if(victorias1 == 3 || victorias2 == 3) {
				System.out.println("Final del concurso. Ha ganado el jugador " + (victorias1 == 3 ? "1" : "2"));
				return true;
			} else {
				return false;
			}
		} finally {
			l.unlock();
		}
	}
}