import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class main {
    
    public static void main(String[] args) {
    	int numCajeros = 3; //N
    	int numClientes = 10; //M
        ArrayList<Cliente>clientes = new ArrayList<Cliente>();
        
        long init = System.currentTimeMillis();  
        
        ExecutorService executor = Executors.newFixedThreadPool(numCajeros);
        for(int i = 0; i < numClientes; i++){	
        	
       	clientes.add(new Cliente(i+1, (int)(Math.random()*11)+2, (int)(Math.random()*11)+2)); 
            Runnable cajera = new Cajeros(clientes.get(i), init);
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