package agua;


import java.util.concurrent.*;

public class GestorAgua {

	private int numHidrogeno = 0;
	private int numOxigeno = 0;
	private Semaphore mutex = new Semaphore(1);
	private Semaphore entraHidrogeno = new Semaphore(1);
	private Semaphore entraOxigeno = new Semaphore(1);
	
	public void hListo(int id) throws InterruptedException{ 

		entraHidrogeno.acquire();

		mutex.acquire();

		numHidrogeno ++;
		System.out.println("Ha entrado una molecula de hidrogeno, llevamos " + numHidrogeno +  " de hidrogeno y " + numOxigeno + " de oxigeno");

		if(numHidrogeno == 2 && numOxigeno == 1) {
			System.out.println("Se ha formado una molecula de agua");
			numHidrogeno = 0;
			numOxigeno = 0;
			entraHidrogeno.release();
			entraOxigeno.release();
		} else if (numHidrogeno < 2){
			entraHidrogeno.release();
		}

		mutex.release();
	}
	
	public void oListo(int id) throws InterruptedException{ 
		entraOxigeno.acquire();

		mutex.acquire();

		numOxigeno ++;
		System.out.println("Ha entrado una molecula de oxigeno, llevamos " + numHidrogeno +  " de hidrogeno y " + numOxigeno + " de oxigeno");

		if(numHidrogeno == 2 && numOxigeno == 1) {
			System.out.println("Se ha formado una molecula de agua");
			numHidrogeno = 0;
			numOxigeno = 0;
			entraHidrogeno.release();
			entraOxigeno.release();
		} 
		
		mutex.release();
	}
}