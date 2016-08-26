package tianlinz_CS201L_inClassPractice;

import java.util.HashMap;
import java.util.LinkedList;

import tianlinz_CS201L_inClassPractice.diff_match_patch.Patch;

public class Merge {

	public static void main(String args[]){
		HashMap<String, String> map = new HashMap<String, String>();
		map.put("KEY", "WRONG!");
		for(HashMap.Entry<String, String> entry: map.entrySet()){
			entry.setValue("CORRECT!");
		}
		System.out.println(map.get("KEY"));
	}
	
	
	public static String mergeStrings(String original, String edit){
		diff_match_patch dmp = new diff_match_patch();
		LinkedList<Patch> patch1 = dmp.patch_make(original, edit);
		String result = (String)(dmp.patch_apply(patch1, original)[0]);
		return result;
	}
}
