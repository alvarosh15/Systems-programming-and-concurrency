
public class Aseos {
	
	private int numClientes = 0;
	private boolean equipoDentro = false;
	private boolean genteDentro = false;
	private boolean equipoQuiereEntrar = false;

	/**
	 * Utilizado por el cliente id cuando quiere entrar en los aseos
	 * CS Version injusta: El cliente espera si el equipo de limpieza est� trabajando
	 * CS Version justa: El cliente espera si el equipo de limpieza est� trabajando o
	 * est� esperando para poder limpiar los aseos
	 * @throws InterruptedException
	 * 
	 */
	public synchronized void entroAseo(int id) throws InterruptedException{

		while(equipoDentro || equipoQuiereEntrar) {
			wait();
		}

		numClientes ++;
		genteDentro = true;
		System.out.println("Ha entrado el cliente " + id + " Hay " + numClientes);
	
	}

	/**
	 * Utilizado por el cliente id cuando sale de los aseos
	 * 
	 */
	public synchronized void salgoAseo(int id){

		numClientes --;

		if(numClientes == 0) {
			genteDentro = false;
			notify();
		}

		System.out.println("Ha salido el cliente " + id + " Hay " + numClientes);
	
	}
	
	/**
	 * Utilizado por el Equipo de Limpieza cuando quiere entrar en los aseos 
	 * CS: El equipo de trabajo est� solo en los aseos, es decir, espera hasta que no
	 * haya ning�n cliente.
	 * @throws InterruptedException
	 * 
	 */
    public synchronized void entraEquipoLimpieza() throws InterruptedException{

		equipoQuiereEntrar = true;

		System.out.println("		El equipo de limpieza quiere entrar");

		while(genteDentro) {
			wait();
		}

		equipoDentro = true;

		System.out.println("		Ha entrado el equipo de limpieza");
		
	}
    
    /**
	 * Utilizado por el Equipo de Limpieza cuando  sale de los aseos 
	 * 
	 * 
	 */
    public synchronized void saleEquipoLimpieza(){
    	
		equipoDentro = false;

		equipoQuiereEntrar = false;

		System.out.println("		Ha salido el equipo de limpieza");

		notifyAll();

	}
}
