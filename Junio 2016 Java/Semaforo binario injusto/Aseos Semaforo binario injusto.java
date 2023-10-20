
import java.util.concurrent.Semaphore;

public class Aseos {
	
	private int numClientes = 0;
	private Semaphore mutex = new Semaphore(1);
	private Semaphore ocupado = new Semaphore(1);
	
	/**
	 * Utilizado por el cliente id cuando quiere entrar en los aseos
	 * CS Version injusta: El cliente espera si el equipo de limpieza est� trabajando
	 * CS Version justa: El cliente espera si el equipo de limpieza est� trabajando o
	 * est� esperando para poder limpiar los aseos
	 * @throws InterruptedException
	 * 
	 */
	public void entroAseo(int id) throws InterruptedException{
		mutex.acquire();
		if(numClientes == 0) {
			ocupado.acquire();
		}
		numClientes ++;
		System.out.println("Ha entrado el cliente " + id + " Hay " + numClientes);
		mutex.release();
	}

	/**
	 * Utilizado por el cliente id cuando sale de los aseos
	 * @throws InterruptedException
	 * 
	 */
	public void salgoAseo(int id) throws InterruptedException{
		mutex.acquire();
		numClientes --;
		System.out.println("Ha salido el cliente " + id + " Hay " + numClientes);

		if(numClientes == 0) {
			ocupado.release();
		}

		mutex.release();
	}
	
	/**
	 * Utilizado por el Equipo de Limpieza cuando quiere entrar en los aseos 
	 * CS: El equipo de trabajo est� solo en los aseos, es decir, espera hasta que no
	 * haya ning�n cliente.
	 * @throws InterruptedException
	 * 
	 */
    public void entraEquipoLimpieza() throws InterruptedException{
		ocupado.acquire();
		System.out.println("Ha entrado el equipo de limpieza");
	}
    
    /**
	 * Utilizado por el Equipo de Limpieza cuando  sale de los aseos 
	 * 
	 * 
	 */
    public void saleEquipoLimpieza(){
		System.out.println("Ha salido el equipo de limpieza");
    	ocupado.release();
	}
}
