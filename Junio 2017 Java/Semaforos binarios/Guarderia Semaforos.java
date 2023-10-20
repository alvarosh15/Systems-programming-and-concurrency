import java.util.concurrent.Semaphore;

public class Guarderia {
	
	private int bebes = 0;
	private int adultos = 0;
	private Semaphore mutex = new Semaphore(1);
	private Semaphore entraBebe = new Semaphore(0);
	private Semaphore saleAdulto = new Semaphore(0);

	/**
	 * Un bebe que quiere entrar en la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro entrar, es decir, hasta que 
	 * cuado entre haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public void entraBebe(int id) throws InterruptedException{

		entraBebe.acquire();

		mutex.acquire();
		bebes ++;
		System.out.println("Ha entrado un bebe, hay " + bebes + " bebes y adultos " + adultos);

		if(bebes + 1 <= 3*adultos) {
			entraBebe.release();
		}

		if(bebes > 3*(adultos - 1) && saleAdulto.availablePermits() == 1) {
			saleAdulto.acquire();
		}

		mutex.release();


		if(bebes > 3*adultos) {
			System.out.println("SE HA ROTO LA CONDICION DE SINCRONIZACION SE HA ROTO LA CONDICION DE SINCRONIZACION");
		}
	}
	/**
	 * Un bebe que quiere irse de la guarderia llama a este metodo * 
	 */
	public void saleBebe(int id) throws InterruptedException{
		mutex.acquire();
		bebes --;
		System.out.println("Ha salido un bebe, hay " + bebes + " bebes y adultos " + adultos);

		if(bebes + 1 == 3*adultos) {
			entraBebe.release();
		}

		if(bebes <= 3*(adultos - 1) && saleAdulto.availablePermits() == 0) {
			saleAdulto.release();
		}

		mutex.release();


		if(bebes > 3*adultos) {
			System.out.println("SE HA ROTO LA CONDICION DE SINCRONIZACION SE HA ROTO LA CONDICION DE SINCRONIZACION");
		}
	}
	/**
	 * Un adulto que quiere entrar en la guarderia llama a este metodo * 
	 */
	public void entraAdulto(int id) throws InterruptedException{

		mutex.acquire();
		adultos ++;
		System.out.println("	Ha entrado un adulto, hay " + bebes + " bebes y adultos " + adultos);

		if(bebes == 3*(adultos - 1) && saleAdulto.availablePermits() == 0) {
			saleAdulto.release();
		}

		if(bebes + 3 == 3*adultos) {
			entraBebe.release();
		}

		mutex.release();

		if(bebes > 3*adultos) {
			System.out.println("SE HA ROTO LA CONDICION DE SINCRONIZACION SE HA ROTO LA CONDICION DE SINCRONIZACION");
		}
	}
	
	/**
	 * Un adulto que quiere irse  de la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro salir, es decir, hasta que
	 * cuando se vaya haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public void saleAdulto(int id) throws InterruptedException{

		saleAdulto.acquire();
		mutex.acquire();
		adultos --;
		System.out.println("	Ha salido un adulto, hay " + bebes + " bebes y adultos " + adultos);

		if(bebes <= 3*(adultos - 1)) {
			saleAdulto.release();
		}

		if(bebes + 1 > 3*adultos && entraBebe.availablePermits() == 1) {
			entraBebe.acquire();
		}

		mutex.release();




		if(bebes > 3*adultos) {
			System.out.println("SE HA ROTO LA CONDICION DE SINCRONIZACION SE HA ROTO LA CONDICION DE SINCRONIZACION");
		}
	}

}
