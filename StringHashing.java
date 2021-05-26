import java.util.*;
/*
Use string hashing (rolling hash precomputation) to determine if str contains sub

Convert letters to numbers. Ex: WORD —> 23, 15, 18, 4
Treat each number as a digit in a base-B system. Ex: B = 29
WORD —> 23 * (29 ^ 3) + 15 * (29 ^ 2) + 18 * (29 ^ 1) + 4 * (29 ^ 0) = 574088
If the number gets too large, do mod M
Base B should be a prime Ex: 29 or 31 (around the size of the alphabet)
Mod M should be a huge prime (collision chance is 1/M) Ex: 10e9 + 7 or 10e9 + 9

Compute hash of every prefix of str.
Ex: str = WORFDWORD
hash(W) = 23
hash(WO) = 23 * 29 + 15 = hash(W) * 29 + 15
hash(WOR) = 23 * (29 ^ 2) + 15 * 29 + 18 = hash(WO) * 29 + 18

Then, use this prefix array to compute the hash of a string (l, r)
Ex: hash(RF) = 18 * 29 + 6 = hash(WORF) – hash(WO) * (29 ^ 2)
hash(l, r) = hash(1, r) – hash(1, l – 1) * B ^ (r – l + 1)
Ex: OR = 23 * (29 ^ 2) + 15 * 29 + 18 - 23 * (29 ^ 2)
*/
public class Main {

	public static void main(String[] args) throws IOException{
    final int MOD = 1000000009;
    Scanner in = new Scanner(System.in);
    String str = in.next(), sub = in.next();
    //calculate the hash of sub as we get the prefix array of str
    int[] prefixArray = new int[str.length() + 1];
    int subHash = 0;
    int j = 0;
    for (int i = 1; i < prefixArray.length; i++){
      prefixArray[i] = (29 * prefixArray[i - 1] + ((int) str.charAt(i - 1) - 65)) % MOD;
      if (j < sub.length()){
        subHash *= 29;
        subHash += (int) sub.charAt(j) - 65;
        j++;
      }
    }
    
    //do the checking
    for (int i = 1; i + sub.length() - 1 < prefixArray.length; i++){
      int temp = prefixArray[i + sub.length() - 1] - prefixArray[i - 1] * (int) Math.pow(29, sub.length());
      if (temp == subHash){
        System.out.println("sub appears in str at index " + i);
      }
    }
	}
}
