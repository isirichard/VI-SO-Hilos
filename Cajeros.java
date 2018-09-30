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
		int numeroCajero = (int)Thread.currentThread().getId()-10;
		System.out.println("La cajera " + numeroCajero
				+ " COMIENZA A PROCESAR LA COMPRA DEL "
				+ this.cliente.getNombre() + " EN EL TIEMPO: "
				+ (System.currentTimeMillis() - this.initialTime) / 1000
				+ "seg");

		// for (int i = 0; i < this.cliente.getCarroCompra().length; i++) {
		// Se procesa el pedido en X segundos
		this.esperarXsegundos(cliente.getTiempoEnCaja());
		System.out.println(this.cliente.getNombre() + " termino en "
				+ "->Tiempo: "
				+ (System.currentTimeMillis() - this.initialTime) / 1000
				+ "seg");
		// }

		
		System.out.println("La cajera " + numeroCajero
				+ " HA TERMINADO DE PROCESAR " + this.cliente.getNombre()
				+ " EN EL TIEMPO: "
				+ (System.currentTimeMillis() - this.initialTime) / 1000
				+ "seg");

	}

	private void esperarXsegundos(int segundos) {
		try {
			Thread.sleep(segundos * 1000);
		} catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}

}