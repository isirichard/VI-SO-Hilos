
public class Personas  extends Thread{
	
	
	long timeSeg = 1000;
	boolean estado;
	int id;
	public Personas(int num,int miId) {
		timeSeg = timeSeg*num;
		this.id = miId;
	}
		
	@Override
	public void run() {
		try {
			Thread.sleep(timeSeg);
			
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		estado = true;
		getEstado();
	}
	public void getEstado() {
		if(estado) {
			System.out.println("cliente "+(id+1)+" termino de elegir productos "+ timeSeg);
			Thread.yield();
		}
		
	}
	
	public void setEstado(boolean miestado) {
		estado = miestado;
	}
	
	
	
}
