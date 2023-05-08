package labLez8;

public class Operaio extends Thread {
	Banco B;
	
	public Operaio(Banco B) {
		this.B = B;
	}
	
	@Override
	public void run() {
		while(true) {
			try {
				Thread.sleep(1000);
				
				B.deposita(20, 14);
			}
			catch (Exception e) {
				System.out.println("ERRORE RUN OPERAIO");
			}
		}
	}
}
