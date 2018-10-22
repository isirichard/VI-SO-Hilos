import java.util.ArrayList;

public class Cola extends Thread {
	private static ArrayList<Integer> cola = new ArrayList<Integer>();

	public Cola() {
	}

	public static void addC(int i) {
		cola.add(i);
	}

	public static int getC(int i) {
		return cola.get(i);
	}

	public static int sizeC() {
		return cola.size();
	}

	public static int sacar(){
		int a = cola.get(0);
		cola.remove(0);
		return a;
	}
}
