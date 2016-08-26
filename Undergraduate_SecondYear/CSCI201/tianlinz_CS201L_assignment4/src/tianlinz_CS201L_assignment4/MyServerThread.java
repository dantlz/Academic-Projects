package tianlinz_CS201L_assignment4;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;

public class MyServerThread extends Thread{

	private ObjectOutputStream oos;
	private ObjectInputStream ois;
	private MyServer server;
	private Socket socket;
		
	public MyServerThread(Socket s, MyServer ms) {
		try {
			socket = s;
			oos = new ObjectOutputStream(s.getOutputStream());
			ois = new ObjectInputStream(s.getInputStream());
			server = ms;
			this.start();
		} catch (IOException ioe) {
			sendResult(new ReturnParcel("ERROR", false));
			ioe.printStackTrace();
		}
	}

	private void sendResult(ReturnParcel result) {
		//Send to client
		try {
			oos.writeObject(result);
			oos.flush();
		} catch (IOException ioe) {
			server.getGUI().fatalServerError();
			ioe.printStackTrace();		
		}
	}
	
	//Check if the given username is available
	private void signUpAvailability(Parcel parcel, ResultSet rSet){
		//Check if it is taken
		server.getGUI().logMessage("Sign-up attempt User:"
				+parcel.getUsername()
				+" Password:"
				+parcel.getPassword());
		boolean taken = false;
		try {
			while (rSet.next()){
				if(parcel.getUsername().equals(rSet.getString("username"))){
					taken = true;
					break;
				}
			}
		} catch (SQLException e) {
			sendResult(new ReturnParcel("ERROR", false));
			e.printStackTrace();
		}
		
		//Log the message 
		if(taken){
			server.getGUI().logMessage("Sign-up Failure User:"
					+parcel.getUsername());	
		}
		else{
			server.getGUI().logMessage("Sign-up Success User:"
					+parcel.getUsername());							
		}
		
		//Send result to client
		sendResult(new ReturnParcel(parcel.getOperation(), taken));
	}
	
	//Query to check if the entered password matches the one in the database for a given username
	private void loginAuthentication(Parcel parcel, ResultSet rSet){
		//print to the serverGUI's log
		server.getGUI().logMessage("Login attempt User:"
				+parcel.getUsername()
				+" Password:"
				+parcel.getPassword());
		
		String pswd = "";
		try {
			if(rSet.next()){
				pswd = rSet.getString("password");
			}
		} catch (SQLException e) {
			sendResult(new ReturnParcel("ERROR", false));
			e.printStackTrace();
		}
		
		//Check for a match
		boolean match = pswd.equals(parcel.getPassword());
		if(match){
			server.getGUI().logMessage("Login Success User:"
					+parcel.getUsername());	
		}
		else{
			server.getGUI().logMessage("Login Failure User:"
					+parcel.getUsername());	
		}
		
		//Send result to client
		sendResult(new ReturnParcel("AUTHENTICATION", match));
	}
	
	//Query for all the files for a given user
	private void getUserFilenames(Parcel parcel, ResultSet rSet){
		Vector<String> files = new Vector<String>();
		try {
			while(rSet.next()){
				files.add(rSet.getString("filename"));
			}
		} catch (SQLException e) {
			sendResult(new ReturnParcel("ERROR", false));
			e.printStackTrace();
		}
		
		//Send the hashmap to client
		sendResult(new ReturnParcel(parcel.getOperation(), files));
	}
	
	private void getUserFileContent(Parcel parcel, ResultSet rSet){
		String content = "";
		try {
			if(rSet.next())
				content = rSet.getString("fileContent");
		} catch (SQLException e) {
			sendResult(new ReturnParcel("ERROR", false));
			e.printStackTrace();
		}
		
		if(content.equals("")){
			server.getGUI().logMessage("File failed to open User:"+parcel.getUsername());	
		}
		else{
			server.getGUI().logMessage("File opened User:"
					+parcel.getUsername()+" File:"+parcel.getPassword());
		}
		
		sendResult(new ReturnParcel(parcel.getOperation(), content, parcel.getPassword()));
	}
	
	public void closeSocket(){
		try {
			socket.close();
		} catch (IOException e) {
			server.getGUI().fatalServerError();
			e.printStackTrace();
		}
	}
	
	public void run() {
		while(true) {
			try {
				//Read from client
				Parcel parcel = (Parcel)ois.readObject();
				Class.forName("com.mysql.jdbc.Driver");
				
				//TODO Change string p to your password
				String p = "YOUR PASSWORD";
				
				Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/tianlinz?useSSL=false&user=root&password="+p);
				Statement st = conn.createStatement();
				PreparedStatement ps = conn.prepareStatement(parcel.getCommand());
				
				//TODO MySQL Print out
				System.out.println("MySQL Command: "+parcel.getCommand());

				//Query
				if(parcel.isQuery()){	
					ResultSet rSet = ps.executeQuery();

					//Signup username availability
					if(parcel.getOperation().equals("AVAILABLE")){	
						signUpAvailability(parcel, rSet);
					}
					
					//Login Authentication
					else if(parcel.getOperation().equals("AUTHENTICATION")){
						loginAuthentication(parcel, rSet);
					}

					//Get all of a user's files
					else if(parcel.getOperation().substring(0, 8).equals("GETFILES")){
						getUserFilenames(parcel, rSet);
					}
					else if(parcel.getOperation().equals("OPENFILE")){
						getUserFileContent(parcel, rSet);
					}
				}
				//Not Query
				else{
					ps.execute();
					//Print to Server GUI Log (getPassword() returns the filename in this case)
					if(parcel.getOperation().equals("SAVEFILE")){
						server.getGUI().logMessage("File saved User:"
								+parcel.getUsername()+" File:"+parcel.getPassword());
					}
					//INSERT username password for sign up
				}
				st.close();
				conn.close();
			} 
			catch (SocketException se){
				System.out.println("Severthread Socket closed");
				this.closeSocket();
				break;
			}
			catch (SQLException sqle) {
				sendResult(new ReturnParcel("ERROR", false));
				sqle.printStackTrace();
			} 
			catch (ClassNotFoundException cnfe) {
				sendResult(new ReturnParcel("ERROR", false));
				cnfe.printStackTrace();
			} catch (IOException e) {
				sendResult(new ReturnParcel("ERROR", false));
				e.printStackTrace();
			}	
		}
	}
}
