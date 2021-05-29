import java.util.*;
import java.io.*;

//find the first occurence of sub in str and prints out its index (using string hashing)
public class StringFinding {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	static StringTokenizer st;
	static String next () throws IOException {
		while (st == null || !st.hasMoreTokens())
			st = new StringTokenizer(br.readLine().trim());
		return st.nextToken();
	}
	
	static final int MOD = 1000000007;
	public static void main(String[] args) throws IOException{
		final int B1 = 29, B2 = 31;
		String str = next(), sub = next();
		long[] strHash29 = new long[str.length()]; calculateHash(strHash29, B1, str); 
		long[] strHash31 = new long[str.length()]; calculateHash(strHash31, B2, str); 
		long[] subHash29 = new long[sub.length()]; calculateHash(subHash29, B1, sub); 
		long[] subHash31 = new long[sub.length()]; calculateHash(subHash31, B2, sub); 
		
		long idealHash29 = getHash(subHash29, B1, 0, sub.length() - 1);
		long idealHash31 = getHash(subHash31, B2, 0, sub.length() - 1);
		for (int i = 0; i + sub.length() - 1< strHash29.length; i++) {
			long curHash29 = getHash(strHash29, B1, i, i + sub.length() - 1);
			long curHash31 = getHash(strHash31, B2, i, i + sub.length() - 1);
			if (idealHash29 == curHash29 && idealHash31 == curHash31) {
				System.out.println(i); return;
			}
		}
		System.out.println(-1);
	}
	
	public static void calculateHash(long[] hash, int B, String str) { //calculate the polynomial hash of str, using base B, stored in hash[] array
		hash[0] = str.charAt(0) - 97;
		for (int i = 1; i < str.length(); i++) {
			hash[i] = ((hash[i - 1] * B) % MOD + str.charAt(i) - 97) % MOD;
		}
	}

	public static long getHash(long[] hash, int B, int a, int b) { //get the hash of a substring, a and b are endpoints of the substring (inclusive)
		if (a == 0) return hash[b] % MOD;
		return (hash[b] - (hash[a - 1] * (int) (pow(B, b - a + 1) % MOD)) % MOD + MOD) % MOD;		
	}
	
	public static long pow(long b, long e){ //O(log n)
		final int MOD = 1000000007;
		b %= MOD;
		long ans = 1;
		while (e > 0){
			if ((e & 1) == 1){
				ans *= b;
			}
			e >>= 1; //divide exponent by 2
			b *= b; //raise base to b^2
			b %= MOD; //mod everything to prevent overflow
			ans %= MOD;
		}
		return ans;
	}
}
