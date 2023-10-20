import java.util.concurrent.Semaphore;

public class Aseos {

	private int numClientes = 0;

	private Semaphore mutex = new Semaphore(1);
	private Semaphore ocupado = new Semaphore(1);
	private Semaphore esperaEquipoLimpieza = new Semaphore(1);
	
	
	/**
	 * Utilizado por el cliente id cuando quiere entrar en los aseos
	 * CS Version injusta: El cliente espera si el equipo de limpieza est� trabajando
	 * CS Version justa: El cliente espera si el equipo de limpieza est� trabajando o
	 * est� esperando para poder limpiar los aseos
	 * @throws InterruptedException
	 * 
	 */
	public void entroAseo(int id) throws InterruptedException{

		esperaEquipoLimpieza.acquire();
		
		mutex.acquire();

		if(numClientes < 1) {
			ocupado.acquire();
		}

		numClientes ++;
		System.out.println("Ha entrado el cliente con id " + id + " Hay " + numClientes);

		mutex.release();
		
		esperaEquipoLimpieza.release();
	}

	/**
	 * Utilizado por el cliente id cuando sale de los aseos
	 * @throws InterruptedException
	 * 
	 */
	public void salgoAseo(int id) throws InterruptedException{
		mutex.acquire();

		numClientes --;
		System.out.println("Ha salido el cliente con id " + id + " Hay " + numClientes);

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

		esperaEquipoLimpieza.acquire();
		System.out.println("El equipo de limpieza quiere entrar");
		ocupado.acquire();
		System.out.println("El equipo de limpieza ha entrado");
		
	}
    
    /**
	 * Utilizado por el Equipo de Limpieza cuando  sale de los aseos 
	 * 
	 * 
	 */
    public void saleEquipoLimpieza(){
		
		System.out.println("El equipo de limpieza sale");
		esperaEquipoLimpieza.release();
		ocupado.release();
	}
}
