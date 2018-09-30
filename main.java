import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class main {
    
    public static void main(String[] args) {
    	int numCajeros = 7; //N
    	int numClientes = 20; //M
        ArrayList<Cliente>clientes = new ArrayList<Cliente>();
        
        for(int i = 0; i < numClientes; i++){
        	String c = "cliente " + String.valueOf(i+1);
        	clientes.add(new Cliente(c, (int)(Math.random()*11)+5)); //rango 5-15
        }
        clientes.add(new Cliente("Cliente 1", 12)); 
        clientes.add(new Cliente("Cliente 2", 5)); 
        clientes.add(new Cliente("Cliente 3", 3)); 
        
        
        long init = System.currentTimeMillis();  
        
        ExecutorService executor = Executors.newFixedThreadPool(numCajeros);
        for (Cliente cliente: clientes) {
            Runnable cajera = new Cajeros(cliente, init);
            executor.execute(cajera);
        }
        executor.shutdown();	// Cierro el Executor
        while (!executor.isTerminated()) {
        	// Espero a que terminen de ejecutarse todos los procesos 
        	// para pasar a las siguientes instrucciones 
        }
        
        long fin = System.currentTimeMillis();	// Instante final del procesamiento
        System.out.println("Tiempo total de procesamiento: "+(fin-init)/1000+" Segundos");
    }
}