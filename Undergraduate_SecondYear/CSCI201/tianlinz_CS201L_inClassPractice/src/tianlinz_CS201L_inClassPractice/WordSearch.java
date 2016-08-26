package tianlinz_CS201L_inClassPractice;

import java.util.Vector;

public class WordSearch {

	public static Vector<Integer> findIndexOfWord(String word, String text){
		Vector<Integer> result = new Vector<>();
		int startingIndex = 0;
		
		for(int i = 0; i <= text.length(); i++){
	
			if(Character.isSpaceChar(text.charAt(i)) || i == text.length()){
				
				String temp = "";
				
				for(char entry: text.substring(startingIndex, i).toCharArray()){
					if( Character.isLetter(entry))
						temp = temp + entry;
				}
				
				System.out.println(temp);
				if(temp.equals(word)){
					result.add(startingIndex);
					result.add(i);
					break;
				}
				startingIndex = i+1;
			}
		}

		return result;
	}
	
	public static void main(String[] args) {
		String test = "test";
		String text = "one two t134hree 1sdhfsdf t123est ";
		Vector<Integer> result = findIndexOfWord(test,text);
		for(Integer entry: result){
			System.out.println(entry);
		}
		System.out.println(text.substring(26, 34));
	}

}
