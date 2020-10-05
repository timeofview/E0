package producer;

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.io.File;

public class Producer {
	public static void main(String[] args) {		
		BufferedReader in = null;
        /*Check per 0 argomenti passati -- da usare per estensioni
        if (args.length == 0){
			System.out.println("Utilizzo: produttore <inputFilename>, bot enough arguments");
			System.exit(0);
		}*/

        /*Accetto infiniti fileName
        for(int i = 0; i<args.length; i++){
            if((!"EOF".equals(args[i].split()))||(!args[i].split().isBlank()){
                arr.add(args[i].split());
            }
            else{
                break;
            }
        }*/

        //Check utilizzo 1 solo argomento
		if (args.length != 1){
			System.out.println("Utilizzo: produttore <inputFilename>");
			System.exit(0);
		}
		
        in = new BufferedReader(new InputStreamReader(System.in));
		FileWriter fout;
		File f = new File(args[0]);
        String inputl = null;
        boolean exists = (f.exists())&&(!f.isDirectory());
		try {
            if(exists){fout = new FileWriter(args[0],true);}
			else{fout = new FileWriter(args[0]);}
            while(true){
				inputl = in.readLine();
                if(inputl.equals("EOF")||inputl.isEmpty()){break;}
                else{
                    inputl=inputl+"\n";
                    fout.write(inputl, 0, inputl.length());
                }
            }	
			fout.close();
		} 
		catch (NumberFormatException nfe) { 
			nfe.printStackTrace(); 
			System.exit(1); // uscita con errore, intero positivo a livello di sistema Unix
		}
	    catch (IOException e) { 
			e.printStackTrace();
			System.exit(2); // uscita con errore, intero positivo a livello di sistema Unix
		}
	}
}

