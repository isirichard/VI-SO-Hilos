import java.util.ArrayList;

public class TiempoCompra extends Thread {
  Cliente cliente;
  ArrayList<Cliente> clientes;
  
  TiempoCompra(Cliente cliente,ArrayList<Cliente> clientes){
    this.cliente = cliente;
    this.clientes = clientes;
    //System.out.println(this.cliente + " " + cliente);
    start();
  }
  
  @Override
  public void run() {
    try {
      //“Cliente i, término de comprar”

      //System.out.println("hilo " + cliente.getNombre()+ " "+cliente.getTiempoComprando());
      sleep(cliente.getTiempoComprando()*1000);
      clientes.add(new Cliente(cliente.getNombre(),cliente.getTiempoEnCaja(),cliente.getTiempoComprando()));
      //System.out.println(clientes);
      //System.out.println(clientes);
      System.out.println(cliente.getNombre()+" ,término de comprar");
    
    } catch (InterruptedException e) {
      e.printStackTrace();
      
    }
  }
  public ArrayList<Cliente> retornar(){
    return clientes;
  }
  
}
