import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Barca {
	
	private int TAM = 3;

	private int pasajeros = 0;
	private int orilla = 1;
	private Lock l = new ReentrantLock();
	private Condition orillaNorte = l.newCondition();
	private Condition orillaSur = l.newCondition();
	private Condition esperaSubirse = l.newCondition();
	private Condition esperaQueAcabeViaje = l.newCondition();
	private Condition genteBarca = l.newCondition();
	private boolean puedeSubirGenteALaBarca = true;
	private boolean puedeBajarGenteBarca = false;
	private boolean haTerminadoViaje = false;

	/*
	 * El Pasajero id quiere darse una vuelta en la barca desde la orilla pos
	 */
	public  void subir(int id,int pos) throws InterruptedException{
		l.lock();
		try {

			if((orilla + 1) % 2 != pos ) {
				if(pos == 1) {
					orillaNorte.await();
				} else if (pos == 0) {
					orillaSur.await();
				}
			}

			if((orilla + 1) % 2 == pos) { // Si la barca está en la orilla
				while(!puedeSubirGenteALaBarca) {
					if(pos == 1) {
						orillaNorte.await();
					} else if (pos == 0) {
						orillaSur.await();
					}
				}
				pasajeros ++;
				System.out.println("El pasajero con id " + id + " se ha subido en la orilla " + (pos == 1 ? "Norte" : "Sur"));
				if(pasajeros == TAM) {
					puedeSubirGenteALaBarca = false;
					puedeBajarGenteBarca = false;
					esperaSubirse.signal();
				}

			} 
		} finally {
			l.unlock();
		}
	}
	
	/*
	 * Cuando el viaje ha terminado, el Pasajero que esta en la barca se baja
	 */
	public  int bajar(int id) throws InterruptedException{
		l.lock();
		try {
			while(!puedeBajarGenteBarca) {
				genteBarca.await();
			}
	
			pasajeros --;
	
			System.out.println("El pasajero con id " + id + " se ha bajado del barco");
	
			if(pasajeros == 0) {
				puedeSubirGenteALaBarca = true;
				haTerminadoViaje = false;
				if((orilla + 1) % 2 == 1) { 
					orillaNorte.signalAll();
				} else { 
					orillaSur.signalAll();
				}
			}
	
			return (orilla + 1) % 2;

		} finally {
			l.unlock();
		}
	}
	/*
	 * El Capitan espera hasta que se suben 3 pasajeros para comenzar el viaje
	 */
	public  void esperoSuban() throws InterruptedException{
		l.lock();
		try {
			while(pasajeros != TAM || haTerminadoViaje) {
				esperaSubirse.await();
			}
	
			System.out.println("			El barco empieza el viaje");
	
			haTerminadoViaje = true;
			esperaQueAcabeViaje.signal();
		} finally {
			l.unlock();
		}
	}
	/*
	 * El Capitan indica a los pasajeros que el viaje ha terminado y tienen que bajarse
	 */
	public  void finViaje() throws InterruptedException{
		l.lock();
		try {
			while(!haTerminadoViaje) {
				esperaQueAcabeViaje.await();
			}
			
			System.out.println("			El barco ha finalizado el viaje");
	
			puedeBajarGenteBarca = true;
			orilla ++;
			genteBarca.signalAll();
		} finally {
			l.unlock();
		}
	}

}
