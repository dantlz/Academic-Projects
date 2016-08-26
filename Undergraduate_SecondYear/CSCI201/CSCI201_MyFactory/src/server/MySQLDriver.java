package server;

import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Connection;
import java.sql.DriverManager;
import org.gjt.mm.mysql.Driver;

public class MySQLDriver {

	private final static String addProduct = "INSERT INTO FACTORYORDERS(NAME, CREATED) VALUES(?,?)";
	private final static String selectName = "SELECT * FROM FACTORYORDERS WHERE NAME = ?";
	private Connection con;
	
	public MySQLDriver() {
		try {
			new Driver();
		} catch (SQLException e) {

		}
	}
	
	public void connect(){
		try{
			con = DriverManager.getConnection("jdbc:mysql://localhost:3306/factory?user=root&password=tackee12321");
		}
		catch(SQLException e){
			
		}
	}
	
	public void stop(){
		try{
			con.close();
		}
		catch(SQLException e){
			
		}
	}
	
	public boolean doesExist(String productName){
		try {
			PreparedStatement ps = con.prepareStatement(selectName);
			ps.setString(1, productName);
			ResultSet result = ps.executeQuery();
			while(result.next()){
				FactoryServerGUI.addMessage(result.getString(1) + " exists with count: "+ result.getInt(2));
				return true;
			}
		} catch (SQLException e) {}
		FactoryServerGUI.addMessage("Unable to find product with name" + productName);
		return false;
	}
	
	public void add(String productName){
		try {
			PreparedStatement ps = con.prepareStatement(addProduct);
			ps.setString(1, productName);
			ps.setInt(2, 0);
			ps.executeUpdate();
			FactoryServerGUI.addMessage("Adding product:" + productName + " to table with count 0");
		} catch (SQLException e) {}
	}
	
}
