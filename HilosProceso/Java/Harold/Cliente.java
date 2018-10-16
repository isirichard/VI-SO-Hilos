
public class Cliente {
	private int numero;
	private int tiempoEnElegirProductos; //el tiempo que demora un cliente al elegir sus productos a comprar
	private int tiempoEnCaja;  //el tiempo que demora en la caja
	
	
	public Cliente(int _numero,int _tiempoEnElegirProductos, int _tiempoEnCaja){
		this.numero=_numero;
		this.tiempoEnElegirProductos = _tiempoEnElegirProductos;
		this.tiempoEnCaja = _tiempoEnCaja;
		
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
	public int getTiempoEnCaja() {
		return tiempoEnCaja;
	}
	public void setTiempoEnCaja(int _tiempoEnCaja) {
		this.tiempoEnCaja = _tiempoEnCaja;
	}
}
