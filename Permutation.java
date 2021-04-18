package CompleteSearch;

import java.util.ArrayList;

public class Permutation {

	public static void main(String[] args) {
		String str = "abcd";
	    int n = str.length();
	    permutation(str.toCharArray(), new ArrayList<Character>(), new boolean[n], n);
	}

	public static void permutation(char[] original, ArrayList<Character> permutation, boolean[] chosen, int n){
	    if (permutation.size() == original.length){ //we have a complete permutation
	      for (char c : permutation) System.out.print(c + " ");
	      System.out.println(); return;
	    }else{
	      for (int i = 0; i < n; i++){
	        if (chosen[i]) continue;
	        chosen[i] = true;
	        permutation.add(original[i]);
	        permutation(original, permutation, chosen, n);
	        chosen[i] = false;
	        permutation.remove(permutation.size() - 1);
	      }
	    }
	 }
	
}
