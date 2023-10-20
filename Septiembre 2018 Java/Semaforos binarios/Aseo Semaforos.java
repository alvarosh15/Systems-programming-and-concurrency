import java.util.concurrent.Semaphore;

public class Aseo {

	private int hombres = 0;
	private int mujeres = 0;
	private Semaphore mutex = new Semaphore(1, true);
	private Semaphore ocupado = new Semaphore(1, true);
	
	/**
	 * El hombre id quiere entrar en el aseo. 
	 * Espera si no es posible, es decir, si hay alguna mujer en ese
	 * momento en el aseo
	 */
	public void llegaHombre(int id) throws InterruptedException{
		mutex.acquire();
		if(hombres == 0) {
			mutex.release();
			ocupado.acquire();
		} else {
			mutex.release();
		}
		mutex.acquire();
		hombres ++;
		System.out.println("Ha entrado un hombre con id " + id + " hay " + hombres);
		mutex.release();
	}
	/**
	 * La mujer id quiere entrar en el aseo. 
	 * Espera si no es posible, es decir, si hay algun hombre en ese
	 * momento en el aseo
	 */
	public void llegaMujer(int id) throws InterruptedException{
		mutex.acquire();
		if(mujeres == 0) {
			mutex.release();
			ocupado.acquire();
		} else {
			mutex.release();
		}
		mutex.acquire();
		mujeres ++;
		System.out.println("Ha entrado una mujer con id " + id + " hay " + mujeres);
		mutex.release();
	}
	/**
	 * El hombre id, que estaba en el aseo, sale
	 */
	public void saleHombre(int id)throws InterruptedException{
		mutex.acquire();
		hombres --;
		System.out.println("Ha salido un hombre con id " + id + " hay " + hombres);
		if(hombres == 0) {
			ocupado.release();
		}
		mutex.release();
	}
	
	public void saleMujer(int id)throws InterruptedException{
		mutex.acquire();
		mujeres --;
		System.out.println("Ha salido una mujer con id " + id + " hay " + mujeres);
		if(mujeres == 0) {
			ocupado.release();
		}
		mutex.release();
	}
}
