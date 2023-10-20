import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Guarderia {
	
	private int numBebes = 0;
	private int numAdultos = 0;
	private Lock l = new ReentrantLock();
	private Condition padresEsperandoSalir = l.newCondition();
	private Condition bebesEsperandoEntrar = l.newCondition();

	
	/**
	 * Un bebe que quiere entrar en la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro entrar, es decir, hasta que 
	 * cuado entre haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public void entraBebe(int id) throws InterruptedException{
		l.lock(); 
		try {
			while(!(numBebes + 1 <= 3*numAdultos)) {
				bebesEsperandoEntrar.await();
			}
			numBebes ++;
			System.out.println("Ha entrado un bebe, hay " + numBebes + " bebes y " + numAdultos + " adultos");

		} finally {
			l.unlock();
		}
	}
	/**
	 * Un bebe que quiere irse de la guarderia llama a este metodo * 
	 */
	public void saleBebe(int id) throws InterruptedException{
		l.lock(); 
		try {
			numBebes --;
			System.out.println("Ha salido un bebe, hay " + numBebes + " bebes y " + numAdultos + " adultos");
			if(numBebes + 1 <= 3*numAdultos) { // Si añadiendo otro bebe más siguen estando de forma segura, les habilito para entrar
				bebesEsperandoEntrar.signal(); // Al salir un bebe como mucho puede entrar otro más
			}
			if(numBebes <= 3*(numAdultos - 1)) { // Si cuando le quito un adulto siguen de forma segura entonces les doy permiso a los padres para salir
				padresEsperandoSalir.signal(); // Al salir un bebe como mucho puede irse un padre
			}
		} finally {
			l.unlock();
		}
	}
	/**
	 * Un adulto que quiere entrar en la guarderia llama a este metodo * 
	 */
	public void entraAdulto(int id) throws InterruptedException{
		l.lock(); 
		try {
			numAdultos ++;
			System.out.println("	Ha entrado un adulto, hay " + numBebes + " bebes y " + numAdultos + " adultos");
			if(numBebes + 1 <= 3*numAdultos) { // Si añadiendo otro bebe más siguen estando de forma segura, les habilito para entrar
				bebesEsperandoEntrar.signalAll(); // Al entrar otro padre pueden entrar hasta 3 bebes
			}
			if(numBebes <= 3*(numAdultos - 1)) { // Si cuando le quito un adulto siguen de forma segura entonces les doy permiso a los padres para salir
				padresEsperandoSalir.signal(); // Al entrar un padre como mucho puede irse un padre
			}
		} finally {
			l.unlock();	
		}
	}
	
	/**
	 * Un adulto que quiere irse  de la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro salir, es decir, hasta que
	 * cuando se vaya haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public void saleAdulto(int id) throws InterruptedException{
		l.lock(); 
		try {
			while(!(numBebes <= 3*(numAdultos-1))) {
				padresEsperandoSalir.await();
			}
			numAdultos --;
			System.out.println("	Ha salido un adulto, hay " + numBebes + " bebes y " + numAdultos + " adultos");
		} finally {
			l.unlock();
		}
	}

}
