
public class Cliente {
	private String nombre;
	private int tiempoEnCaja; //el tiempo que demora que una caja termine de atender a un cliente
	private int tiempoComprando;
	
	public Cliente(String _nombre, int _tiempoEnCaja,int _tiempoComprando){
		this.nombre=_nombre;
		this.tiempoEnCaja=_tiempoEnCaja;
		this.tiempoComprando=_tiempoComprando;
	}
	public String getNombre() {
		return nombre;
	}
	public int getTiempoComprando() {
    return tiempoComprando;
  }
  public void setTiempoComprando(int tiempoComprando) {
    this.tiempoComprando = tiempoComprando;
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
