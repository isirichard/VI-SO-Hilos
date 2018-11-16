import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
/*
Simular el comportamiento de los cajeros de un supermercado:
• N es la cantidad de cajeros. Se determina desde el inicio
• M cantidad de clientes (M se genera aleatoriamente). Los clientes se identifican
por un número.
• Ti tiempo de atención del cliente i-ésimo en una caja (se genera aleatoriamente)
• Ci tiempo en el que el cliente i-ésimo elige sus productos (se genera
aleatoriamente)
Un cajero solo puede atender a otro cliente si el tiempo del anterior se termino.
Solo existe una cola para todas las cajas.
Los clientes seleccionan sus productos por un tiempo C, después del cual van a
las cajas. Cuando esto ocurra, mostrar un mensaje parecido a: “Cliente i, término
de comprar”, (i número del cliente)
Cada vez que un cliente haya sido atendido por un cajero, mostrar un mensaje
parecido a “Cliente i ha sido atendido por el Cajero j” (i número de cliente, j
número del cajero).
*/

public class main {
  static ArrayList<Cliente> clientes = new ArrayList<Cliente>();
  
  public static void main(String[] args) throws InterruptedException {
    int numCajeros = 2; // N
    int numClientes = 7; // M
    //ArrayList<Cliente> clientes = new ArrayList<Cliente>();
    /*
     * for(int i = 0; i < numClientes; i++){ String c = "cliente " +
     * String.valueOf(i+1); clientes.add(new Cliente(c,
     * (int)(Math.random()*11)+5)); //rango 5-15 }
     */
    
    TiempoCompra uno = new TiempoCompra(new Cliente("Cliente 1" , 2, 7),clientes);
    TiempoCompra dos = new TiempoCompra(new Cliente("Cliente 2" , 3, 6),clientes);
    TiempoCompra tres = new TiempoCompra(new Cliente("Cliente 3" , 3, 5),clientes);
    TiempoCompra cuatro = new TiempoCompra(new Cliente("Cliente 4" , 3, 4),clientes);
    TiempoCompra cinco = new TiempoCompra(new Cliente("Cliente 5" , 3, 3),clientes);
    TiempoCompra seis = new TiempoCompra(new Cliente("Cliente 6" , 3, 2),clientes);
    TiempoCompra siete = new TiempoCompra(new Cliente("Cliente 7" , 3, 1),clientes);
    
    
    //uno.start();
    //dos.start();
    //clientes = uno.retornar();
    //System.out.println(clientes);
    /*
    clientes.add(new Cliente("Cliente 1", 2, 2));
    clientes.add(new Cliente("Cliente 2", 1, 3));
    clientes.add(new Cliente("Cliente 3", 3, 2));
    clientes.add(new Cliente("Cliente 4", 2, 1));
    clientes.add(new Cliente("Cliente 5", 1, 3));
    clientes.add(new Cliente("Cliente 6", 2, 2));
    */
    //System.out.println("numero de procesos");
    //System.out.println(siete.isAlive());
    uno.join();
    dos.join();
    tres.join();
    cuatro.join();
    cinco.join();
    seis.join();
    siete.join();
    long init = System.currentTimeMillis();

    ExecutorService executor = Executors.newFixedThreadPool(numCajeros);
    for (int i = 0; i<clientes.size();i++) {
      Runnable cajera = new Cajeros(clientes.get(i), init);
      // new Thread(cajera).sleep(cliente.getTiempoComprando()*1000);
      // System.out.println(cliente.getNombre()+", término de comprar");
      executor.execute(cajera);
    }
    executor.shutdown(); // Cierro el Executor
    while (!executor.isTerminated()) {
      // Espero a que terminen de ejecutarse todos los procesos
      // para pasar a las siguientes instrucciones
    }

    long fin = System.currentTimeMillis(); // Instante final del procesamiento
    System.out.println("Tiempo total de procesamiento: " + (fin - init) / 1000 + " Segundos");
    

  }


}