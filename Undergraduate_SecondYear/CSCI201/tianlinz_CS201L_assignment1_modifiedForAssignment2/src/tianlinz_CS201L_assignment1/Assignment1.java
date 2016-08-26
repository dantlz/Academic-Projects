package tianlinz_CS201L_assignment1;
import java.io.File;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Vector;

public class Assignment1 {	
	private String txt;
	private String kb;
	private String wl;
	
	//Constructor
	public Assignment1(String txt, String kb, String wl) {
		this.txt = txt;
		this.kb = kb;
		this.wl = wl;
	}
	
	//Remove any non-alphabet chars from a string
	private static String removeNonAlpha(String str){
		String result = "";
		for(char current: str.toCharArray()){
			if( Character.isLetter(current) || Character.isSpaceChar(current))
				result = result + current;
		}
		return result;
	}

	//Calculate the difference/score between two string
	private int difference(String error, String suggestion){
		int count = 0;
		for(int i = 0; i < error.length(); i++){
			if(error.charAt(i) != suggestion.charAt(i))
				count++;			
		}
		count = count + suggestion.length() - error.length();
		return count;
	}

	//Recurse through all possible corrections of a string while checking for prefix completions
	private void findSuggestionsHelper(String originalWord, String currentWord, Integer index, Vector<String> suggestions, HashMap<Character, String> neighbors, Trie trie){
		//Base case
		if(index == originalWord.length()){
			//Contains as prefix also checks for contains as word.
			if(trie.containsAsPrefix(currentWord))
				suggestions.addAll(trie.getWordsForPrefix(currentWord));
			return;
		}

		//If the current string is a prefix to some word, or this is the start of recursion, we'll allow the recursion to continue
		if(trie.containsAsPrefix(currentWord) || currentWord == ""){
			//It is important to allow the chars in the original word to recurse as well
			findSuggestionsHelper(originalWord, currentWord + originalWord.toCharArray()[index], index+1, suggestions, neighbors, trie);
			//Recurse through all neighboring keys
			for(char ch: neighbors.get(originalWord.charAt(index)).toCharArray()){
				findSuggestionsHelper(originalWord, currentWord+ch, index+1, suggestions, neighbors, trie);
			}
		}
	}

	//Main spell check function
	public Vector<Vector<String>> spellCheck(){
		//File paths and variables
		String wordList_file = wl;
		String keyboard_file = kb;
		Scanner scnr;
		Vector<String> text = new Vector<String>();
		HashMap<Character, String> keyboard = new HashMap<Character, String>();
		Trie trie = new Trie();	
		Vector<String> errors = new Vector<String>();
		Vector<Vector<String>> results = new Vector<Vector<String>>();

		txt = txt.replaceAll(System.lineSeparator(), " ");
		String[] textHolder= txt.split(" ");	

		for(String entry: textHolder){
			entry= removeNonAlpha(entry.toLowerCase());	
			if(entry != "")
				text.addElement(entry);
		}
		if(text.size() == 0)
			return null;

		//Put all word list words in a trie
		try{
			scnr = new Scanner(new File(wordList_file));
			while(scnr.hasNext()){
				String next = removeNonAlpha(scnr.next()).toLowerCase();
				if(next != ""){
					trie.insert(next);	
				}
			}
			scnr.close();
		}		
		catch(Exception e){}
		//empty trie
		if(trie.isEmpty()){
			return null;
		}


		//Put keyboard in a map
		try{
			scnr = new Scanner(new File(keyboard_file));
			while(scnr.hasNext()){
				//Assuming all chars are in lower case and there are no special chars except the ',' separator.
				String current = scnr.nextLine();
				char c = current.charAt(0);
				String neighbors = c+current.substring(2, current.length());
				keyboard.put(c, neighbors);
			}
			scnr.close();
		}		
		catch(Exception e){}		


		//Find all errors
		for(String word: text){
			if(!trie.containsAsWord(word)){
				errors.addElement(word);
			}
		}

		//No errors found
		if(errors.size() == 0 )
			return null;

		//For every error
		for(int i = 0; i < errors.size(); i ++){

			//Variables
			String error = errors.elementAt(i);
			Vector<String> suggestions = new Vector<String>();
			HashMap<String, Integer> suggestionScores = new HashMap<String, Integer>();
			Vector<String> topTen = new Vector<>();

			//Find completions
			if(trie.containsAsPrefix(error)){
				suggestions = trie.getWordsForPrefix(error);
			}
			
			//Find corrections or completions based on a correction
			findSuggestionsHelper(error, "", 0, suggestions, keyboard, trie);	
			//Sort the suggestions and remove duplicate
			Collections.sort(suggestions);
			for(int a = 0; a < suggestions.size()-1; a++){
				if(suggestions.elementAt(a).equals(suggestions.elementAt(a+1))){
					suggestions.remove(a);
					a--;
				}
			}
			
			//No suggestions
			if(suggestions.size() == 0){
				topTen.insertElementAt(error, 0);
				results.add(topTen);				
				continue;
			}

			//Loop all suggestions through that to get a score
			for(String entry: suggestions){
				suggestionScores.put(entry, difference(error, entry));
			}


			//Find top 10 suggestions based on scores
			for(int g = 0; g < 10 && (!suggestionScores.isEmpty()); g++){

				//Set the smallest one				
				String smallest = suggestions.get(0);
				int min = suggestionScores.get(smallest);

				//Go through map to find if there is an even smaller one
				for(Map.Entry<String, Integer> entry: suggestionScores.entrySet()){
					if(entry.getValue() < min){
						min = entry.getValue();
						smallest = entry.getKey();
					}
				}
				
				//Add the smallest to topTen, and remove it from suggestions list and score list
				topTen.addElement(smallest);
				suggestionScores.remove(smallest);
				suggestions.remove(smallest);

				//On the 10th suggestion, reset i if there are multiple suggestions with the same score.
				if(g == 9){
					for(Map.Entry<String, Integer> entry: suggestionScores.entrySet()){
						if(entry.getValue() == min)
							g = 8;
					}
				}
			}
			
			topTen.insertElementAt(error, 0);
			results.add(topTen);
		}

		
		//Write the errors vector to a text filer		 
		//errors contain the suggestions	
		return results;
	}
}