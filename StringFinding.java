import java.util.*;
import java.io.*;

//count the number of permutations of needle (n) that is present in the haystack (h)
public class StringFinding {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	static StringTokenizer st;
	static String next () throws IOException {
		while (st == null || !st.hasMoreTokens())
			st = new StringTokenizer(br.readLine().trim());
		return st.nextToken();
	}
	
	public static void main(String[] args) throws IOException{
		final int B = 9973, MOD1 = 1000000007, MOD2 = 1000000009;
		String n = next(), h = next();
		if (n.length() > h.length()) {
			System.out.println(0); return;
		}
		
		//there might be string collision (different strings with same hash)
		//so for each substring, calculate its polynomial has with 2 different MODs
		//store (polynomial hash 1, polynomial hash2) in a set to ensure all distinct permutations are stored
		Set<ArrayList<Long>> set = new HashSet<>(); 
		//since order of permutations are different
		//cannot use traditional polynomial hashing to determine if this substring is a permutation of the needle
		//instead, for each hash of the substrings, compute (B + s1) * (B + s2) * .. * (B + sk) mod M and check if that value is equal to that of the needle
		long idealHash1 = 1, idealHash2 = 1, hash1 = 1, hash2 = 1;
		//all substrings being added to set need to have the same hash (calculated above) as the needle
		//polyhash is used to distinct between different substrings (that are permutations of needle) when we add them to set
		//polynomial hash(l, r) = polynomial hash(1, r) - polynomial hash(1, l - 1) * B ^ (r - l + 1)
		long polyHash1 = 0, polyHash2 = 0;
		long pow1 = 1, pow2 = 1;
		for (int i = 0; i < n.length(); i++) {
			idealHash1 = idealHash1 * (B + (int) n.charAt(i) - 97) % MOD1;
			idealHash2 = idealHash2 * (B + (int) n.charAt(i) - 97) % MOD2;
			hash1 = hash1 * (B + (int) h.charAt(i) - 97) % MOD1;
			hash2 = hash2 * (B + (int) h.charAt(i) - 97) % MOD2;
			polyHash1 = (polyHash1 * B + ((int) h.charAt(i) - 97)) % MOD1;
			polyHash2 = (polyHash2 * B + ((int) h.charAt(i) - 97)) % MOD2;
			pow1 = pow1 * B % MOD1;
			pow2 = pow2 * B % MOD2;
		}
		if (idealHash1 == hash1 && idealHash2 == hash2) {
			ArrayList<Long> list = new ArrayList<>();
			list.add(polyHash1); list.add(polyHash2);
			set.add(list);
		}
		
		for (int i = n.length(); i < h.length(); i++) {
			hash1 = hash1 * inverse(B + (int) h.charAt(i - n.length()) - 97, MOD1) % MOD1 * (B + (int) h.charAt(i) - 97) % MOD1;
			hash2 = hash2 * inverse(B + (int) h.charAt(i - n.length()) - 97, MOD2) % MOD2 * (B + (int) h.charAt(i) - 97) % MOD2;
			
			polyHash1 = (polyHash1 * B - (int) (h.charAt(i - n.length()) - 97 ) * pow1 % MOD1 + (int) h.charAt(i) - 97 + MOD1) % MOD1;
			polyHash2 = (polyHash2 * B - (int) (h.charAt(i - n.length()) - 97 ) * pow2 % MOD2 + (int) h.charAt(i) - 97 + MOD2) % MOD2;
			if (idealHash1 == hash1 && idealHash2 == hash2) {
				ArrayList<Long> list = new ArrayList<>();
				list.add(polyHash1); list.add(polyHash2);
				set.add(list);
			}
		}
		System.out.println(set.size());
	}

  //find modular inverse
	public static long inverse(long base, long MOD) {
		long ans = 1L, e = MOD - 2;
		while (e > 0) {
			if ((e & 1) == 1) ans = ans * base % MOD;
			e >>= 1;
			base = base * base % MOD;
		}
		return ans; 
	}

}
