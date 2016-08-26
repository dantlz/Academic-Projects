package tianlinz_CS201L_assignment4;

import java.io.Serializable;
import java.util.Vector;

public class ReturnParcel implements Serializable {

	private static final long serialVersionUID = 1L;
	
	private String operation;
	private boolean result;
	private Vector<String> filenames;
	private String content;
	private String filename;
	
	//Parcel to return bool value
	public ReturnParcel(String o, boolean r){
		operation = o;
		result = r;
	}
	
	//Parcel to return vector of strings
	public ReturnParcel(String o, Vector<String> f){
		operation = o;
		filenames = f;
	}
	
	//Parcel to return a string content
	public ReturnParcel(String o, String c, String fn){
		operation = o;
		content = c;
		filename = fn;
	}
	
	public String getOperation(){
		return operation;
	}
	
	public boolean getResult(){
		return result;
	}
	
	public Vector<String> getFilenames(){
		return filenames;
	}
	
	public String getFilename(){
		return filename;
	}
	
	public String getContent(){
		return content;
	}
}
