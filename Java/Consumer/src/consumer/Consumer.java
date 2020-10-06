package consumer;

import java.io.FileNotFoundException;
import java.io.FileReader;

public class Consumer {

	public static void main(String[] args) {
		Character ignore = null;
		int length = args.length;
		try {
			ignore = args[0].charAt(0);
		} catch (IndexOutOfBoundsException e) {
			System.out.println("Sintassi non corretta.");
		}
		for (int i = 1; i < length; i++) {
			try {
				new MyReader(new FileReader(args[i]), ignore).start();
			} catch (FileNotFoundException e) {
				System.out.println("Errore nell'apertura file "+args[i]);
			}
		}
	}

}
