
public class mainBanco {
	
	public static void main(String [] args) throws InterruptedException {
		int N = 5;
		
		Personas listaClientes[];
		
		listaClientes = new Personas [N];
		listaClientes[0] = new Personas(2,0);
		listaClientes[1] = new Personas(4,1);
		listaClientes[2] = new Personas(1,2);
		listaClientes[3] = new Personas(5,3);
		listaClientes[4] = new Personas(7,4);
		
		//inicia los hilos en paralelo
		for(int i = 0; i < N; i++) {
			listaClientes[i].start();
			
		}
	}

}
