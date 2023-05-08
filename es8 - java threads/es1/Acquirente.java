package labLez8;

public class Acquirente extends Thread {
	Banco B;
	
	public Acquirente(Banco B) {
		this.B = B;
	}
	
	public void run() {
		Boolean OK = true;
	
		while (true) {
			try {
				Thread.sleep(1000);
				
				OK = B.acquista(8, 9);
				
				if (!OK) this.stop();
			}
			catch (Exception e) {
				System.out.println("Errore nell'acquisto");
			}
		}
	}
}
