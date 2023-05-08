package labLez8;

public class Main {

	public static void main(String[] args) {
		Banco B = new Banco();
		
		Operaio [] Op = new Operaio[1];
		Acquirente [] Ac = new Acquirente[3];
		
		for (int i=0; i<Op.length; i++) {
			Op[i] = new Operaio(B);
			Op[i].start();
		}
		
		try {
			Thread.sleep(2000);
			for (int i=0; i<Ac.length; i++) {
				Ac[i] = new Acquirente(B);
				Ac[i].start();
			}
		}
		catch (Exception e) {
			System.out.println("Errore start acquirenti");
		}
		
		try {
			Thread.sleep(5000);
			
			for (int i=0; i<Op.length; i++)
				Op[i].stop();
			
			for (int i=0; i<Ac.length; i++)
				Ac[i].stop();
			
			B.stop();
		}
		catch (Exception e) {
			System.out.println("Errore nel main");
		}
		
		B.stampa();
	}

}
