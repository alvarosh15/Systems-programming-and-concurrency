
public class Tiovivo {

	private int MAX_TAM;
	private int pasajeros = 0;
	private boolean puedenSubirse = false;
	private boolean puedenEmpezarSubirse = true;
	private boolean puedeEmpezarViaje = false;
	private boolean puedenBajarse = false;
	
	public Tiovivo(int tam) {
		MAX_TAM = tam;
	}
	
	public synchronized void subir(int id) throws InterruptedException 
	{	
		while(!puedenSubirse) {
			wait();
		}
		pasajeros ++;
		System.out.println("Se ha subido el pasajero con id " + id + " Ya van " + pasajeros + " falta " + (MAX_TAM - pasajeros));
		if(pasajeros == MAX_TAM) {
			puedenSubirse = false;
			puedenEmpezarSubirse = false;
			puedeEmpezarViaje = true;
			notify();
		}
	}
	
	public synchronized void bajar(int id) throws InterruptedException 
	{
		while(!puedenBajarse) {
			wait();
		}
		pasajeros --;
		System.out.println("Se ha bajado el pasajero con id " + id + " Ya van " + pasajeros);
		if(pasajeros == 0) {
			puedenEmpezarSubirse = true;
			notifyAll();
		}
	}
	
	public synchronized void esperaLleno () throws InterruptedException 
	{
		while(!puedenEmpezarSubirse) {
			wait();
		}
		puedenSubirse = true;
		puedenBajarse = false;
		System.out.println("		El tiovivo está parado, pueden subirse los pasajeros de la cola");
		notifyAll();
	}
	
	public synchronized void finViaje () throws InterruptedException 
	{
		while(!puedeEmpezarViaje) {
			wait();
		}
		System.out.println("		El tiovivo ha acabado, pueden bajarse los pasajeros");
		puedenBajarse = true;
		notifyAll();
	}
}
