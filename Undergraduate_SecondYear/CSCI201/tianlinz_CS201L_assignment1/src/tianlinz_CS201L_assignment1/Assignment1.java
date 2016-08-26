package tianlinz_CS201L_assignment1;
import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Calendar;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Vector;

public class Assignment1 {

	
	//Remove any non-alphabet chars from a string
	public static String removeNonAlpha(String str){
		String result = "";
		for(char current: str.toCharArray()){
			if( Character.isLetter(current) )
				result = result + current;
		}
		return result;
	}

	//Calculate the difference/score between two string
	public static int difference(String error, String suggestion){
		int count = 0;
		for(int i = 0; i < error.length(); i++){
			if(error.charAt(i) != suggestion.charAt(i))
				count++;			
		}
		count = count + suggestion.length() - error.length();
		return count;
	}

	//Recurse through all possible corrections of a string while checking for prefix completions
	public static void findSuggestions(String originalWord, String currentWord, Integer index, Vector<String> suggestions, HashMap<Character, String> neighbors, Trie trie){
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
			findSuggestions(originalWord, currentWord + originalWord.toCharArray()[index], index+1, suggestions, neighbors, trie);
			//Recurse through all neighboring keys
			for(char ch: neighbors.get(originalWord.charAt(index)).toCharArray()){
				findSuggestions(originalWord, currentWord+ch, index+1, suggestions, neighbors, trie);
			}
		}
	}

	public static void main(String args[]){
		//File paths and variables
		String wordList_file = "";
		String keyboard_file = "";
		String text_file = "";
		File file = null;
		Scanner scnr = new Scanner(System.in);
		Vector<String> text = new Vector<String>();
		Vector<String> errors = new Vector<String>();
		HashMap<Character, String> keyboard = new HashMap<Character, String>();
		Trie trie = new Trie();	
		
		//Check for multiple wl, kb, txt files
		for(int i = 0; i < args.length ; i++){
			String lastThreeChars = args[i].substring(args[i].length()-3, args[i].length());
			if(lastThreeChars.equals(".wl")){
				//Check for invalid files here.
				try{	
					file = new File(args[i]);
					if( (!file.isFile()) || (!file.canRead()) ){
						continue;
					}
				}
				catch(Exception e){}
				wordList_file = args[i];
			}
			else if(lastThreeChars.equals(".kb")){
				try{	
					file = new File(args[i]);
					if( (!file.isFile()) || (!file.canRead()) ){
						continue;
					}
				}
				catch(Exception e){}
				keyboard_file = args[i];
			}
			else if(lastThreeChars.equals("txt")){
				try{	
					file = new File(args[i]);
					if( (!file.isFile()) || (!file.canRead()) ){
						continue;
					}
				}
				catch(Exception e){}
				text_file = args[i];
			}						
		}

		
		//Make sure all files input
		while(true){	
			if(wordList_file != "" && keyboard_file !="" && text_file != ""){
				break;
			}	
			if(wordList_file == ""){
				System.out.print("Please enter a word list file: ");
				String temp = scnr.next();
				if(temp.length() < 4){
					System.out.println("Inputted file name too short, please enter another one: ");
					continue;			
				}
				else{
					if( temp.substring(temp.length()-3, temp.length()).equals(".wl")){
						try{	
							file = new File(temp);
							if( (!file.isFile()) || (!file.canRead()) ){
								System.out.println("The entered file could not be opened, please enter another one.");
								continue;
							}
						}
						catch(Exception e){}
						wordList_file = temp;
					}
					else{
						System.out.println("Inputted file name does not end with .wl, please enter another one: ");
						continue;
					}			
				}

			}
			if(keyboard_file == ""){
				System.out.print("Please enter a keyboard file: ");	
				String temp = scnr.next();
				if(temp.length() < 4){
					System.out.println("Inputted file name too short, please enter another one: ");
					continue;	
				}
				else{
					if( temp.substring(temp.length()-3, temp.length()).equals(".kb")){
						try{	
							file = new File(temp);
							if( (!file.isFile()) || (!file.canRead()) ){
								System.out.println("The entered file could not be opened, please enter another one.");
								continue;
							}
						}
						catch(Exception e){}
						keyboard_file  = temp;
					}
					else{
						System.out.println("Inputted file name does not end with .kb, please enter another one: ");
						continue;
					}		
				}
			}
			if(text_file == ""){
				System.out.print("Please enter a text file: ");		
				String temp = scnr.next();
				if(temp.length() < 5){
					System.out.println("Inputted file name too short, please enter another one: ");
					continue;	
				}
				else{
					if( temp.substring(temp.length()-3, temp.length()).equals("txt")){
						try{	
							file = new File(temp);
							if( (!file.isFile()) || (!file.canRead()) ){
								System.out.println("The entered file could not be opened, please enter another one.");
								continue;
							}
						}
						catch(Exception e){}
						text_file  = temp;
					}
					else{
						System.out.println("Inputted file name does not end with .txt, please enter another one: ");
						continue;
					}	
				}
			}
		}
		scnr.close();

		
		//Put all text in vector
		try{
			scnr = new Scanner(new File(text_file));
		}
		catch(Exception e){}
		while(scnr.hasNext()){
			String next = removeNonAlpha(scnr.next()).toLowerCase();
			if(next != "")
				text.addElement(next);
		}
		scnr.close();
		if(text.size() == 0){
			System.out.println("Empty text file. Exiting program.");
			System.exit(1);
		}		


		//Put all word list words in a trie
		try{
			scnr = new Scanner(new File(wordList_file));
		}		
		catch(Exception e){}
		while(scnr.hasNext()){
			String next = removeNonAlpha(scnr.next()).toLowerCase();
			if(next != "")
				trie.insert(next);		
		}
		scnr.close();
		//Check for failure to open file.
		if(trie.isEmpty()){
			System.out.println("Empty word list file. Exiting program.");
			System.exit(1);
		}


		//Put keyboard in a map
		try{
			scnr = new Scanner(new File(keyboard_file));
		}		
		catch(Exception e){}		
		while(scnr.hasNext()){
			//Assuming all chars are in lower case and there are no special chars except the ',' separator.
			String current = scnr.nextLine();
			char c = current.charAt(0);
			String neighbors = c+current.substring(2, current.length());
			keyboard.put(c, neighbors);
		}
		scnr.close();
		//Check for failure to open file.
		if(trie.isEmpty()){
			System.out.println("Empty keyboard file. Exiting program.");
			System.exit(1);
		}


		//Find all errors
		for(String word: text){
			if(!trie.containsAsWord(word)){
				errors.addElement(word);
			}
		}


		//No errors found
		if(errors.size() == 0 ){
			System.out.println("No errors found, exciting program.");
			System.exit(0);
		}


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
			findSuggestions(error, "", 0, suggestions, keyboard, trie);	
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
				errors.set(i, error + " -");
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

			//Concatenate the error with " - " followed by top 10 suggestions.
			String result = "";
			for(String s: topTen)
				result = result + " " + s;
			errors.set(i, error + " -" + result);
		}


		//Write the errors vector to a text file		 
		String temp = new java.sql.Timestamp(Calendar.getInstance().getTime().getTime()).toString().substring(0, 19);
		String fileName = "";
		for(char ch: temp.toCharArray()){
			if(Character.isDigit(ch))
				fileName += ch;
			else
				fileName += "_";
		}
		Path output = Paths.get(fileName);
		try{
			Files.write(output, errors, Charset.forName("UTF-8"));
		}
		catch(Exception e){
			System.out.println("Something went wrong when writing to output file, exiting program");
			System.exit(1);
		}		
	}
}