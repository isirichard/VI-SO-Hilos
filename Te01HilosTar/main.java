import java.util.ArrayList;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class main extends Cola {
	public static void main(String args[]) throws InterruptedException {
		int numClientes, numCajeros;
		Scanner sc = new Scanner(System.in);

		System.out.println("-----Iniciando simulador de Supermercado-----");
		System.out.println("Ingrese la cantidad de cajeros");
		numCajeros = sc.nextInt();
		int r = 10;
		System.out.println("El numero de clientes se genera automaticamente y es "+ r);
		numClientes = r;
		
		ArrayList<Cliente> clientes = new ArrayList<>();

		for (int i = 0; i < numClientes; i++) {
			clientes.add(new Cliente(i + 1, random(4, 20)));
			clientes.get(i).start();
		}
		//clientes.get(0).join();

		ExecutorService executor = Executors.newFixedThreadPool(numCajeros);
		for (int j = 0; j < numClientes; j++) {
			Runnable cajera = new Cajero(random(8, 15)); //no acepta hilos solo acepta runeables
			executor.execute(cajera);
		}
		executor.shutdown(); // Cierro el Executor
		while (!executor.isTerminated()) {
			// Espero a que terminen de ejecutarse todos los procesos
			// para pasar a las siguientes instrucciones
		}
	}

	public static int random(int min, int max) {
		int range = (max - min) + 1;
		return (int) (Math.random() * range) + min;
	}
	
}
