
public class Cliente {
	private String nombre;
	private int tiempoEnCaja; //el tiempo que demora que una caja termine de atender a un cliente
	
	public Cliente(String _nombre, int _tiempoEnCaja){
		this.nombre=_nombre;
		this.tiempoEnCaja=_tiempoEnCaja;
		
	}
	public String getNombre() {
		return nombre;
	}
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}
	public int getTiempoEnCaja() {
		return tiempoEnCaja;
	}
	public void setTiempoEnCaja(int _tiempoEnCaja) {
		this.tiempoEnCaja = _tiempoEnCaja;
	}
}
