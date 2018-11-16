public class Cajeros implements Runnable {

	private Cliente cliente;
	private long initialTime;

	public Cajeros(Cliente cliente, long initialTime) {
		this.cliente = cliente;
		this.initialTime = initialTime;
	}

	public void setCliente(Cliente cliente) {
		this.cliente = cliente;
	}

	public long getInitialTime() {
		return initialTime;
	}

	public void setInitialTime(long initialTime) {
	this.initialTime = initialTime;
	}

	@Override
	public void run() {
		int numeroCajero = (int)Thread.currentThread().getId()-8;
		this.esperarTiempoElegir(cliente.getTiempoEnElegirProductos());
		//System.out.println("El cliente " + this.cliente.getNumero() + " demoro " + cliente.getTiempoEnElegirProductos() + " seg en elegir sus productos");
		System.out.println("El cliente " +this.cliente.getNumero()+ " termino de comprar");
		this.esperarTiempoEnCaja(cliente.getTiempoEnCaja());
		//System.out.println("La cajera " + numeroCajero + " HA TERMINADO DE PROCESAR " + this.cliente.getNumero() + " EN EL TIEMPO: " + (System.currentTimeMillis() - this.initialTime) / 1000 + "seg");
		System.out.println("El cliente "+ this.cliente.getNumero() +" ha sido atendido por el cajero: "+numeroCajero);
	
	}

	private void esperarTiempoElegir(int segundos) { //dormir al hilo, esperar que el cliente se tome su tiempo para elegir sus productos para luego seguir con la siguiente instruccion 
		try {
			Thread.sleep(segundos * 1000);
		} catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}
	private void esperarTiempoEnCaja(int segundos) { //dormir al hilo, esperar que el cajero atienda a algun cliente para luego seguir con la siguiente instruccion 
		try {
			Thread.sleep(segundos * 1000);
		} catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}
}