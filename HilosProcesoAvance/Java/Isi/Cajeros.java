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
	

	public void sleep(int num){
	  
	}
	
	@Override
	public void run() {
		int numeroCajero = (int)Thread.currentThread().getId()-15;
		this.esperarXsegundos(cliente.getTiempoEnCaja());
		System.out.println(this.cliente.getNombre() + " ha sido atendido por el cajero "
        + numeroCajero);

	}

	private void esperarXsegundos(int segundos) {
		try {
			Thread.sleep(segundos * 1000);
		} catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}

}