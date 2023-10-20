import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Aseos {
	
	private int numClientes = 0;
	private Lock l = new ReentrantLock();
	private Condition esperaFueraAseo = l.newCondition();
	private boolean equipoDentro = false;
	private boolean equipoQuiereEntrar = false;

	/**
	 * Utilizado por el cliente id cuando quiere entrar en los aseos
	 * CS Version injusta: El cliente espera si el equipo de limpieza est� trabajando
	 * CS Version justa: El cliente espera si el equipo de limpieza est� trabajando o
	 * est� esperando para poder limpiar los aseos
	 * @throws InterruptedException
	 * 
	 */
	public void entroAseo(int id) throws InterruptedException{
		l.lock();
		try {
			while(equipoDentro || equipoQuiereEntrar) {
				esperaFueraAseo.await();
			}
			numClientes ++;
			System.out.println("Ha entrado el cliente " + id + " Hay " + numClientes);
		} finally {
			l.unlock();
		}
	}

	/**
	 * Utilizado por el cliente id cuando sale de los aseos
	 * 
	 */
	public void salgoAseo(int id){
		l.lock();
		try {
			numClientes --;
			if(numClientes == 0) {
				esperaFueraAseo.signal();
			}
			System.out.println("Ha salido el cliente " + id + " Hay " + numClientes);
		} finally {
			l.unlock();
		}
	}
	
	/**
	 * Utilizado por el Equipo de Limpieza cuando quiere entrar en los aseos 
	 * CS: El equipo de trabajo est� solo en los aseos, es decir, espera hasta que no
	 * haya ning�n cliente.
	 * @throws InterruptedException
	 * 
	 */
    public void entraEquipoLimpieza() throws InterruptedException{
		l.lock();
		try {
			equipoQuiereEntrar = true;
			System.out.println("		El equipo de limpieza quiere entrar");
			while(numClientes > 0) {
				esperaFueraAseo.await();
			}
			equipoDentro = true;
			System.out.println("		El equipo de limpieza ha entrado");
		} finally {
			l.unlock();
		}
	}
    
    /**
	 * Utilizado por el Equipo de Limpieza cuando  sale de los aseos 
	 * 
	 * 
	 */
    public void saleEquipoLimpieza(){
		l.lock();
		try {
			equipoDentro = false;
			equipoQuiereEntrar = false;
			System.out.println("		El equipo de limpieza ha salido");
			esperaFueraAseo.signalAll();
		} finally {
			l.unlock();
		}
	}
}
