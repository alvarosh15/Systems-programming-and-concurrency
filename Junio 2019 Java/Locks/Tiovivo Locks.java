import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Tiovivo {
		
	private int MAX_TAM;
	private int pasajeros = 0;
	private Lock l = new ReentrantLock();
	private Condition esperando = l.newCondition();
	private Condition esperaTiovivo = l.newCondition();
	private Condition genteTiovivo = l .newCondition();
	private boolean bajarse = false;
	private boolean puedenEmpezarSubirse = true;
	private boolean subirse = false;


	public Tiovivo(int tam) {
		MAX_TAM = tam;
	}

	public void subir(int id) throws InterruptedException 
	{	
		l.lock();
		try {
			while(!subirse) {
				esperando.await();
			}
			pasajeros ++;
			System.out.println("Se ha subido el pasajero con id " + id + " Ya van " + pasajeros + " falta " + (MAX_TAM - pasajeros));
			if(pasajeros == MAX_TAM) {
				puedenEmpezarSubirse = false;
				subirse = false;
				genteTiovivo.signal();
			}
		} finally {
			l.unlock();
		}
	}
	
	public void bajar(int id) throws InterruptedException 
	{
		l.lock();
		try {
			while(!bajarse) {
				genteTiovivo.await();
			}
			pasajeros --;
			System.out.println("Se ha bajado el pasajero con id " + id + " Ya van " + pasajeros);
			if(pasajeros == 0) {
				puedenEmpezarSubirse = true;
				esperaTiovivo.signalAll();
			}

		} finally {
			l.unlock();
		}
	}
	
	public void esperaLleno () throws InterruptedException 
	{
		l.lock();
		try {
			while(!puedenEmpezarSubirse) {
				esperaTiovivo.await();
			}
			subirse = true;
			bajarse = false;
			System.out.println("		El tiovivo está parado, pueden subirse los pasajeros de la cola");
			esperando.signalAll();
		} finally {
			l.unlock();
		}			
	}
	
	public void finViaje () throws InterruptedException 
	{
		l.lock();
		try {
			while(pasajeros < MAX_TAM) {
				genteTiovivo.await();
			}
			System.out.println("		El tiovivo ha acabado, pueden bajarse los pasajeros");
			bajarse = true;
			genteTiovivo.signalAll();
		} finally {
			l.unlock();
		}	
	}
}
