package tianlinz_CS201L_assignment4;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.Vector;

public class MyServer extends Thread{
	
	private Vector<MyServerThread> serverThreads;
	private int port;
	private MyServerGUI gui;
	private ServerSocket ss;
	
	public MyServer(int p, MyServerGUI g){
		serverThreads = new Vector<MyServerThread>();
		port = p;
		gui = g;
		this.start();
	}
	
	//Interrupt server and all serverthreads
	public void stopServer(){
		for(MyServerThread mst: serverThreads){
			mst.closeSocket();
		}
		if(ss != null){
			try {
				ss.close();
			} catch (IOException e) {
				gui.fatalServerError();
				e.printStackTrace();
			}
		}
		
	}
	
	//Return the server GUI to update the log message
	public MyServerGUI getGUI(){
		return gui;
	}
	
	public void run(){
		//Create new server socket and add a new serverthread to the vector of threads whenever a new client connects
		ss = null;
		try {
			ss = new ServerSocket(port);
			//Continuously listens for new clients
			while (true) {
				Socket s = ss.accept();
				MyServerThread st = new MyServerThread(s, this);
				serverThreads.add(st);
			}
		} 
		catch (SocketException se){
			System.out.println("Server socket closed");
		}
		catch (IOException ioe) {
			gui.fatalServerError();
			ioe.printStackTrace();
		} 
		finally {
			if (ss != null) {
				try {
					ss.close();
				} 
				catch (IOException ioe) {
					gui.fatalServerError();
					ioe.printStackTrace();	
				}
			}
		}

	}

}
