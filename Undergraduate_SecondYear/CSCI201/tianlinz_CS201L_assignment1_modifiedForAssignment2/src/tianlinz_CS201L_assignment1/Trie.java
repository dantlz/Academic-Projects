package tianlinz_CS201L_assignment1;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

public class Trie {
	//Trie node
	class Node {
	    char value;
	    boolean isWord;
	    boolean isLeaf;
	    HashMap<Character, Node> next = new  HashMap<Character, Node>();
	    
	    public Node(){}
	    
	    public Node(char val){
	        this.value = val;
	        this.isWord = false;
	        this.isLeaf = false;
	    }
	}
	
	//Trie root
    private Node root;
    
    //Constructor
    public Trie() {
        root = new Node();
    }
 
    // Insert
    public void insert(String word) {
        HashMap<Character, Node> next = root.next;
        
        //Loop through the word to be added
        for( int i = 0; i < word.length(); i++){
        	//Get the chars one by one
            char current = word.charAt(i);
 
            Node path = null;
            
            if(next.containsKey(current)){
            	path = next.get(current);
            	if(i != word.length() - 1 && path.isLeaf)
            		path.isLeaf = false;
            }
            else{
                path = new Node(current);
                next.put(current, path);
            }
 
            next = path.next;
 
            if(i == word.length() - 1){
                path.isLeaf = true;   
                path.isWord = true;
            }
        }
    }
 
    //Find
    public boolean containsAsWord(String word) {
    	
    	Node result = get(word);
    	
    	if(result == null)
    		return false;
    	return result.isWord;
    }
    
    //Find prefix
    public boolean containsAsPrefix(String word) {
    	Node result = get(word);

    	return result != null;
    }
    
    //If the trie is empty
    public boolean isEmpty(){
    	return root.next.size() == 0;
    }

    //Print all Node values
    public static void print(Node root){
    	System.out.println(root.value);
    	for(Map.Entry<Character, Node> entry: root.next.entrySet() ){
    		print(entry.getValue());
    	}
    }
       
    //Get a certain Node.
    public Node get(String str){
        HashMap<Character, Node> next = root.next;
        Node path = null;
        
        //Loop through the word to be added
        for( int i = 0; i < str.length(); i++){
        	//Get the chars one by one
            char current = str.charAt(i);
  
            if(next.containsKey(current)){
            	path = next.get(current);
            }
            else{
            	return null;
            }
 
            next = path.next;
        }
        return path;
    }
    
    //Get all words with a given prefix
    public Vector<String> getWordsForPrefix(String prefix){
    	Node probe = get(prefix);
    	Vector<String> result = new Vector<String>();
    	if(probe == null)
    		return result;
    	getWordsHelper(prefix, probe, result);
    	return result;
    }

    //Recursive part of getWordsForPrefix
    private void getWordsHelper(String prefix, Node probe, Vector<String> result){

    	if(probe.isWord){
    		result.addElement(prefix);
    	}
    	
    	
    	if(probe.next.size() == 0 )
    		return ;
    	else{
    		for(Map.Entry<Character, Node> entry: probe.next.entrySet()){
    			getWordsHelper(prefix + entry.getKey(), entry.getValue(), result);
    		}    		
    		return;
    	}
    }  
}
