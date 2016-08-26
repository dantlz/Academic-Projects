package tianlinz_CS201L_assignment4;

import java.io.Serializable;

public class Parcel  implements Serializable{
	private static final long serialVersionUID = 1L;
	private boolean isQuery;
	private String operation;
	private String command;
	private String username;
	private String password;

	public boolean isQuery() {
		return isQuery;
	}

	public String getOperation() {
		return operation;
	}
	
	
	public String getCommand() {
		return command;
	}
	
	public String getUsername(){
		return username;
	}
	
	public String getPassword(){
		return password;
	}


	public Parcel(Boolean isQuery, String operation, String command, String username, String password) {
		this.isQuery = isQuery;
		this.operation = operation;
		this.command = command;
		this.username = username;
		this.password = password;
	}
	
}
