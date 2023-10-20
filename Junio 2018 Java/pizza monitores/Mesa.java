
public class Mesa {
	
	private int porciones = 0;

	private boolean pizzaPedida = false;
	private boolean pagada = false;
	private boolean primeroCome = false;
	
	/**
	 * 
	 * @param id
	 * El estudiante id quiere una ración de pizza. 
	 * Si hay una ración la coge y sigue estudiante.
	 * Si no hay y es el primero que se da cuenta de que la mesa está vacía
	 * llama al pizzero y
	 * espera hasta que traiga una nueva pizza. Cuando el pizzero trae la pizza
	 * espera hasta que el estudiante que le ha llamado le pague.
	 * Si no hay pizza y no es el primer que se da cuenta de que la mesa está vacía
	 * espera hasta que haya un trozo para él.
	 * @throws InterruptedException 
	 * 
	 */
	public synchronized void nuevaRacion(int id) throws InterruptedException{

		if(porciones == 0 && !pizzaPedida) {
			primeroCome = false;
			pizzaPedida = true;
			System.out.println("El estudiante con id: " + id + " ha pedido una pizza");
			notifyAll();
			while (porciones == 0) {
				wait();
			}
			System.out.println("El estudiante con id: " + id + " paga la pizza");
			pagada = true;
			notifyAll();
			porciones--;
			System.out.println("El estudiante con id: " + id + " se come un trozo de pizza. Trozos restantes: " + porciones);
			primeroCome = true;
			notifyAll();
		} else if(porciones == 0) {
			while(porciones == 0 && !primeroCome) {
				wait();
			}
		} else {
			porciones --;
			System.out.println("El estudiante con id: " + id + " se come un trozo de pizza. Trozos restantes: " + porciones);
		}
	}


	/**
	 * El pizzero entrega la pizza y espera hasta que le paguen para irse
	 * @throws InterruptedException 
	 */
	public synchronized void nuevoCliente() throws InterruptedException{
		System.out.println("El pizzero entrega la pizza");
		porciones = 8;
		pizzaPedida = false;
		notifyAll();
		while(!pagada) {
			wait();
		}
		pagada = false;
		System.out.println("El pizzero ha sido pagado");
	}
	

/**
	 * El pizzero espera hasta que algún cliente le llama para hacer una pizza y
	 * llevársela a domicilio
	 * @throws InterruptedException 
	 */
	public synchronized void nuevaPizza() throws InterruptedException{

		while(!pizzaPedida) {
			wait();
		}
		System.out.println("El pizzero ha hecho una pizza y la ha llevado a domicilio");

	}

}
