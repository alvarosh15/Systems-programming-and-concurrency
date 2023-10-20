import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;

public class SalaImpresorasS implements SalaImpresoras {

    private int impresorasDadas;
    private Semaphore mutex = new Semaphore(1, true);
    private Semaphore hayImpresoras = new Semaphore(1, true);
    private List<Integer> impresoras = new LinkedList<>();

    public SalaImpresorasS (int tam) {
        impresorasDadas = tam;
        for(int i = 0; i < tam; i ++) {
            impresoras.add(i);
        }
    }

    @Override
    public int quieroImpresora(int id) throws InterruptedException {

        System.out.println("Cliente " + id + " quiere impresora ");

        hayImpresoras.acquire();
        
        mutex.acquire();

        impresorasDadas --;

        System.out.println("Cliente " + id + " coge impresora " + impresoras.get(0) + " quedan libres " + impresorasDadas);

        if(impresorasDadas > 0) {
            hayImpresoras.release();
        }

        int impresora = impresoras.remove(0);

        mutex.release();

        return impresora;
    }

    @Override
    public void devuelvoImpresora(int id, int n) throws InterruptedException {
        mutex.acquire();

        impresorasDadas ++;

        System.out.println("Cliente " + id + " devuelve la impresora " + n + " quedan libres " + impresorasDadas);

        impresoras.add(n);

        if(impresorasDadas == 1) {
            hayImpresoras.release();
        }

        mutex.release();
        
    }
    
}
