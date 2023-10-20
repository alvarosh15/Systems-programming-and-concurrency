import java.util.concurrent.Semaphore;

public class Tiovivo {
		
	private int MAX_TAM;

	private int pasajeros = 0;
	private Semaphore puedenSubirse = new Semaphore(0);
	private Semaphore puedenBajarse = new Semaphore(0);
	private Semaphore lleno = new Semaphore(0);
	private Semaphore puedoEmpezar = new Semaphore(1);
	private Semaphore mutex = new Semaphore(1);

	public Tiovivo(int tam) {
		MAX_TAM = tam;
	}
	
	public void subir(int id) throws InterruptedException 
	{	
		puedenSubirse.acquire();
		mutex.acquire();
		pasajeros ++;
		System.out.println("Se ha subido el pasajero con id " + id + " Ya van " + pasajeros + " falta " + (MAX_TAM - pasajeros));
		if(pasajeros == MAX_TAM) {
			lleno.release();
		} else {
			puedenSubirse.release();
		}
		mutex.release();
	}
	
	public void bajar(int id) throws InterruptedException 
	{
		puedenBajarse.acquire();
		mutex.acquire();
		pasajeros --;
		System.out.println("Se ha bajado el pasajero con id " + id + " Ya van " + pasajeros);
		if(pasajeros == 0) {
			puedoEmpezar.release();
		} else {
			puedenBajarse.release();
		}
		mutex.release();
	}
	
	public void esperaLleno () throws InterruptedException 
	{
		puedoEmpezar.acquire();
		System.out.println("		El tiovivo está parado, pueden subirse los pasajeros de la cola");
		puedenSubirse.release();
	}
	
	public void finViaje () 
	{
		puedenBajarse.release();
		System.out.println("		El tiovivo ha acabado, pueden bajarse los pasajeros");
	}
}
