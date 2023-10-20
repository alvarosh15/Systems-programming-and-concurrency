

public class Guarderia {

	private int numAdultos = 0;
	private int numBebes = 0;
	private boolean seguroParaBebeEntrar = false;
	private boolean seguroParaPadreSalir = false;
	
	/**
	 * Un bebe que quiere entrar en la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro entrar, es decir, hasta que 
	 * cuado entre haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public synchronized void entraBebe(int id) throws InterruptedException{
		while(!seguroParaBebeEntrar) {
			wait();
		}
		numBebes ++;
		System.out.println("Ha entrado un bebe, hay " + numBebes + " bebes y " + numAdultos + " adultos");
		if(numBebes + 1 > 3*numAdultos) { // Si soy el ultimo bebe en entrar de forma segura paro para que el resto no pueda entrar
			seguroParaBebeEntrar = false;
		} 
		if (numBebes > 3*(numAdultos - 1)) { // Si con este nuevo bebe en entrar al salir un padre ya no es seguro, les prohibo salir
			seguroParaPadreSalir = false;
		} 
	}
	/**
	 * Un bebe que quiere irse de la guarderia llama a este metodo * 
	 */
	public synchronized void saleBebe(int id) throws InterruptedException{
		numBebes --;
		System.out.println("Ha salido un bebe, hay " + numBebes + " bebes y " + numAdultos + " adultos");
		if(numBebes + 1 <= 3*numAdultos) { // Si añadiendo otro bebe más siguen estando de forma segura, les habilito para entrar
			seguroParaBebeEntrar = true;
		}
		if(numBebes <= 3*(numAdultos - 1)) { // Si cuando le quito un adulto siguen de forma segura entonces les doy permiso a los padres para salir
			seguroParaPadreSalir = true;
		}
		notifyAll();
	}
	/**
	 * Un adulto que quiere entrar en la guarderia llama a este metodo * 
	 */
	public synchronized void entraAdulto(int id) throws InterruptedException{
		numAdultos ++;
		System.out.println("	Ha entrado un adulto, hay " + numBebes + " bebes y " + numAdultos + " adultos");
		if(numBebes + 1 <= 3*numAdultos) { // Ahora es seguro para que los bebes entren, les permito pasar 
			seguroParaBebeEntrar = true;
		}
		if(numBebes <= 3*(numAdultos - 1)) { // Si quitando un padre siguen estando bien, entonces pueden salir
			seguroParaPadreSalir = true;
		}
		notifyAll();
	}
	
	/**
	 * Un adulto que quiere irse  de la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro salir, es decir, hasta que
	 * cuando se vaya haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public synchronized void saleAdulto(int id) throws InterruptedException{	
		while(!seguroParaPadreSalir) {
			wait();
		}
		numAdultos --;
		System.out.println("	Ha salido un adulto, hay " + numBebes + " bebes y " + numAdultos + " adultos");
		if(numBebes > 3*(numAdultos - 1)) { // Si el numero de bebes es el numero de adultos, dejo de dejar salir a los padres
			seguroParaPadreSalir = false;
		} 
		if(numBebes + 1 > 3*numAdultos) { // Compruebo si puede entrar otro bebe, si no puede se lo prohibo
			seguroParaBebeEntrar = false;
		} 
	}

}
