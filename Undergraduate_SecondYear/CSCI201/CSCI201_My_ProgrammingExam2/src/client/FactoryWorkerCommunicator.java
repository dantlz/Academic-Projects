package client;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStreamWriter;
import java.net.ConnectException;
import java.net.Socket;
import java.util.Vector;
import decode.Decoder;

public class FactoryWorkerCommunicator extends Thread{
	
	private Vector<String> receivedStrings = new Vector<String>();
	private Socket socket;
	private BufferedReader br;
	private BufferedWriter bw;
//	private ObjectOutputStream objectOutputStream;
	private String name;
	public boolean authorized = false;
	private FactoryWorker worker;

	public FactoryWorkerCommunicator(String name, FactoryWorker worker){
		this.name = name;
		this.worker = worker;
		try {
			socket = new Socket("localhost", 6687);
			this.bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
			this.br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//			objectOutputStream = new ObjectOutputStream(socket.getOutputStream());

		}
		catch (ConnectException ce){
			ce.printStackTrace();
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		} 	
	}


	public void startAuthentication(){
		worker.mLock.lock();
		try {
			System.out.println("Authorizing");
			System.out.println("Writing name: " + name);
			bw.write(name + "\n");
			bw.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	//This works except decoding is too slow.
	
	synchronized public void receiveDecodedMessag(String a){
		count ++ ;
		whole = whole+ a;
		if(count == 20){
			System.out.println("20!!!!");
			try {
				bw.write(whole);
				worker.ready();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	int count = 0;
	String whole = "";

	
	public void run(){		
		try {
			while (true) {
				String line = br.readLine();
				System.out.println("Received: " + line);
				DecoderThread thread = new DecoderThread(line, this);
				thread.start();
			}
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}
	
}
