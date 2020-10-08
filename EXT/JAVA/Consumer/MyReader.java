package consumer;

import java.io.IOException;
import java.io.Reader;

class MyReader extends Thread {
	private Reader reader;
	private Character ignore;

	public MyReader(Reader reader, Character ignore) {
		this.reader = reader;
		this.ignore = ignore;
	}

	public void run() {
		try {
			int in;
			char ch;
			while ((in = reader.read()) >= 0) {
				ch = (char) in;
				if (ch != ignore.charValue()) {
					System.out.print(ch);
				}
			}
			reader.close();
		} catch (IOException e) {
			System.out.println("Errore nella lettura del file");
			System.exit(2);
		}
	}
}
