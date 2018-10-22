public class Cajero implements Runnable {
	private int id;
	private int tiempo;

	public Cajero(int _tiempo) {
		tiempo = _tiempo;
	}

	@Override
	public void run() {
		tiempoEspera(tiempo);
		if(Cola.sizeC() > 0){
		int cliente = Cola.sacar();	
		String numeroCajero = Thread.currentThread().getName().substring(14,Thread.currentThread().getName().length());
		System.out.println("El cliente " + cliente + " fue atendido por el cajero " + numeroCajero + " en " +tiempo + " seg");
		}
	}

	private void tiempoEspera(int segundos) {
		try {
			Thread.sleep(segundos * 1000);
		} catch (InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
	}
}
