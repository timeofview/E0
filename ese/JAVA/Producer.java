public class Producer
{public static void main(String[] args)
	{ BufferedReader in = null; int res = 0;
	// fare controllo argomenti
	if (args.length != 1){
		System.out.println("Utilizzo: produttore <inputFilename>");
		System.exit(0);
		}
	in = new BufferedReader(new InputStreamReader(System.in));
	FileWriter fout; String inputl;
		try { fout = new FileWriter(args[0]);
			System.out.println("Inserisci la nuova riga");
			inputl = in.readLine()+"\n";
			while(inputl != null)
			{ 	
				fout.write(inputl, 0, inputl.length());
				System.out.println("Inserisci la nuova riga");
				inputl = in.readLine()+"\n";
			}
			fout.close();
	}
	catch (NumberFormatException nfe) {nfe.printStackTrace(); System.exit(1);}
	catch (IOException e) {e.printStackTrace(); System.exit(2);}
	}
