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
				
				if (!OK) {
					Boolean canExit = false;
					while(!canExit) {
						Thread.sleep(1000);
						canExit = B.acquista(8, 9);
						OK = canExit;
					}
				}
			}
			catch (Exception e) {
				System.out.println("Errore nell'acquisto");
			}
		}
	}
}
