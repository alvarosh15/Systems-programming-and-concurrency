
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Parada {

	private int contPasajeros = 0;
	private boolean hayBus = false;
	private Lock l = new ReentrantLock(true);
	private Condition cola = l.newCondition();
	private Condition esperaBus = l.newCondition();
	private int i;
	
	public Parada(){

	}
	/**
	 * El pasajero id llama a este metodo cuando llega a la parada.
	 * Siempre tiene que esperar el siguiente autobus en uno de los
	 * dos grupos de personas que hay en la parada
	 * El metodo devuelve el grupo en el que esta esperando el pasajero
	 * 
	 */
	public int esperoBus(int id) throws InterruptedException{
		l.lock();
		try {
			System.out.println("El pasajero " + id + " ha llegado a la parada.");
			if (hayBus) {
				i = 1;
			} else {
				i = 0;
				contPasajeros++;
			}
			cola.await();
			return i; //comentar esta línea
		} finally {
			l.unlock();
		}
	}
	/**
	 * Una vez que ha llegado el autobús, el pasajero id que estaba
	 * esperando en el grupo i se sube al autobus
	 *
	 */
	public void subeAutobus(int id,int i) throws InterruptedException{
		l.lock();
		try {
			while (i != 0 || !hayBus) {
				cola.await();
				i = 0;
				contPasajeros++;
			}
			System.out.println("\t El pasajero " + id + " se ha subido al autobús.");
			contPasajeros--;
			esperaBus.signal();
		} finally {
			l.unlock();
		}
	}
	/**
	 * El autobus llama a este metodo cuando llega a la parada
	 * Espera a que se suban todos los viajeros que han llegado antes
	 * que el, y se va
	 * 
	 */
	public void llegoParada() throws InterruptedException{
		l.lock();
		try {
			System.out.println("\t El autobús ha llegado a la parada.");
			hayBus = true;
			cola.signalAll();
			while (contPasajeros > 0) {
				esperaBus.await();
			}
			System.out.println("El autobús se va de la parada.");
			hayBus = false;
			cola.signalAll();
		} finally {
			l.unlock();
		}
	}
}
