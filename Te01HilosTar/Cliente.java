
public class Cliente extends Cola {
	private int numero;
	private int tiempoEnElegirProductos; //el tiempo que demora un cliente al elegir sus productos a comprar
	
	public Cliente(int id){
		numero = id;
	}
	public Cliente(int id, int _tiempoEnElegirProductos){
		numero = id;
		tiempoEnElegirProductos = _tiempoEnElegirProductos;
	}
	
	public int getNumero() {
		return numero;
	}
	public void setNumero(int _numero) {
		this.numero = _numero;
	}
	public int getTiempoEnElegirProductos() {
		return tiempoEnElegirProductos;
	}
	public void setTiempoEnElegirProductos(int _tiempoEnElegirProductos) {
		this.tiempoEnElegirProductos = _tiempoEnElegirProductos;
	}
	

	@Override
	public void run() {	
		tiempoEspera(this.tiempoEnElegirProductos);
		System.out.println("el cliente "+ numero+ " demoro en elegir sus productos en " + tiempoEnElegirProductos + " seundos");
		Cola.addC(numero);
	}
	
	private void tiempoEspera(int segundos) {
		try {
			Thread.sleep(segundos * 1000);
		} catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}
	
}
