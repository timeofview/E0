import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;


public class Producer {
	public static void main(String[] args) {		
		
		final int maxFileNumber = 9;
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String inputl = null;
		ArrayList<String> righe = new ArrayList<String>();
		String[] tmp;
		int tmpValue;
		FileWriter[] fout= new FileWriter[args.length];

        //Check per 0 argomenti passati
        if (args.length == 0 || args.length > maxFileNumber){
			System.out.println("Utilizzo: produttore <inputFilename1> ... <inputFilename9>");
			System.exit(0);
		}

		//Check se il file esiste già
		boolean exists[] = new boolean[args.length];
		for(int i = 0; i < args.length; i++){
			exists[i] = (Files.exists(Paths.get(args[i])))&&(!Files.isDirectory(Paths.get(args[i])));	
		}

		//Ciclo infinito in Input fino alla stringa "EOF" o riga vuota
		while(true){
			try{
				//Leggo la riga
				System.out.println("Inserisci <fileNumber>: <messaggi>(riga vuota o scrivi EOF per terminare):");
				inputl = in.readLine();

				//Check in ingresso per caratteri terminatori
				if(inputl.equals("EOF")||inputl.isEmpty()){break;}
				else{
					//Aggiungo il newline char
					inputl=inputl+"\n";
					righe.add(inputl);
				}
			}
			catch (IOException e) { 
				e.printStackTrace();
				System.exit(1); // uscita con errore, intero positivo a livello di sistema Unix
			}
		}

		//Chiudo Input
		try{in.close();}
		catch (IOException e) { 
			e.printStackTrace();
			System.exit(2); // uscita con errore, intero positivo a livello di sistema Unix
		}

		//Ciclo di apertura dei FileWriter
		for(int i = 0; i < args.length; i++){
			try{
				//Se il file esiste scrivo in append
				if(exists[i]){
					fout[i] = new FileWriter(args[i],true);
				}
				//Altrimenti viene creato
				else{
					fout[i] = new FileWriter(args[i]);
				}
			}
			catch (IOException e) { 
				e.printStackTrace();
				System.exit(3); // uscita con errore, intero positivo a livello di sistema Unix
			}
		}

		//Ciclo di valutazione Input e Scrittura su file
		for(String riga : righe){
			try{
				//Controlli sull'indice
				tmp = riga.split(":");
				//Controllo sulla corretta impostazione della riga
				if(tmp.length!=2){
					System.out.println("Formato riga: <Filenumber> Stringa");
					System.exit(4); // uscita con errore, intero positivo a livello di sistema Unix
				}
				//Parse dell'intero
				tmpValue = Integer.parseInt(tmp[0].trim());  
				//Controlli sul valore
				if(tmpValue<1||tmpValue>maxFileNumber||tmpValue>args.length){
					System.out.println("Inserito un indice per un file non valido");
					System.exit(5);
				}
				//Shifto Indietro di 1 perchè i file sono numerati da 1 a 9
				fout[tmpValue-1].write(tmp[1], 0, tmp[1].length());
			}
			catch (NumberFormatException nfe) {
				nfe.printStackTrace(); 
				System.exit(6); // uscita con errore, intero positivo a livello di sistema Unix
			}
			catch (IOException e) {
				e.printStackTrace(); 
				System.exit(7); // uscita con errore, intero positivo a livello di sistema Unix
			}
		}

		//Ciclo di chiusura dei FileWriter
		for(int i = 0; i < args.length; i++){
			try{
				fout[i].close();
			}
			catch (IOException e) { 
				e.printStackTrace();
				System.exit(8); // uscita con errore, intero positivo a livello di sistema Unix
			}
		}
	}
}
