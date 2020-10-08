package consumer;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;

public class Consumer {

	public static void main(String[] args) {
		char ignore='x';
		Reader reader;
		int length = args.length;
		try {
			ignore = args[0].charAt(0);
		} catch (IndexOutOfBoundsException e) {
			System.out.println("Sintassi non corretta.");
			System.exit(1);
		}
		for (int i = 1; i < length; i++) {
			try {
				reader = new FileReader(args[i]);
				int in;
				char ch;
				while ((in = reader.read()) >= 0) {
					ch = (char) in;
					if (ch != ignore) {
						System.out.print(ch);
					}
				}
				reader.close();
				
			} catch (FileNotFoundException e) {
				System.out.println("Errore nell'apertura file "+args[i]);
			}catch (IOException e) {
				System.out.println("Errore nella lettura del file");
				System.exit(2);
			}
		}
	}
}
