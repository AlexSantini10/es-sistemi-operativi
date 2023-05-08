package labLez8;

public class Banco extends Thread {
	int fragole_disp;
	int asparagi_disp;
	float incasso;
	
	Boolean debug = true ;
	
	public Banco() {
		this.fragole_disp = 0;
		this.asparagi_disp = 0;
		
		this.incasso = 0;
	}
	
	public Banco(int fragole_disp, int asparagi_disp) {
		this.fragole_disp = fragole_disp;
		this.asparagi_disp = asparagi_disp;
		
		this.incasso = 0;
	}
	
	public void setfragole_disp(int fragole_disp) {
		this.fragole_disp = fragole_disp;
	}
	
	public int getfragole_disp() {
		return this.fragole_disp;
	}
	
	public void setasparagi_disp(int asparagi_disp) {
		this.asparagi_disp = asparagi_disp;
	}
	
	public int getasparagi_disp() {
		return this.asparagi_disp;
	}
	
	public synchronized Boolean acquista(int quantFragole, int quantAsparagi) {
		if (this.fragole_disp >= quantFragole && this.asparagi_disp >= quantAsparagi) {
			this.fragole_disp -= quantFragole;
			this.asparagi_disp -= quantAsparagi;
			
			if (this.debug)
				this.stampa();
			
			this.incasso += quantFragole + quantAsparagi;
			return true;
		}
		else return false;
	}
	
	public synchronized void deposita(int quantFragole, int quantAsparagi) {
		this.fragole_disp += quantFragole;
		this.asparagi_disp += quantAsparagi;
		
		if (this.debug)
			this.stampa();
	}
	
	public synchronized void stampa() {
		System.out.println("Il banco ha attualmente " + this.incasso + "€, sono disponibili " 
				+ this.fragole_disp + " fragole e " 
				+ this.asparagi_disp + " asparagi");
	}
}
