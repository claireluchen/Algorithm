package CompleteSearch;

import java.util.ArrayList;
import java.util.Scanner;

/*
a set of n apples, each with a given weight
put the apples into two baskets, print the minimum weight difference between the two baskets

generate all possible subsets
use bitmask to determine whether to pick an apple or not
10010: apples corresponding to 1s will be put into basket 1, otherwise put into basket 2
a << b means shifting the bits of a by b positions to the left, resulting value is a * (2 ^ b)

1 << x has only the xth bit turned on in binary (2 ^ x)
& operator takes two integers and return a new integer whose ith bit is turned on if and only if
the ith bit is turned on for both a and b. this is used to check is we take the apple at ith position
(ex: for 10010, we only want to put apples from positions 1 and 4 into basket 1. we know positions 
1 and 4 are 1s because 10010 & 10 and 10010 & 10000 return a positive number. for all other positions,
such as position 3, 10010 & 1000 -> 0).
*/
public class Subsets {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] apples = new int[n];
		for (int i = 0; i < n; i++) apples[i] = in.nextInt();
		
		long minDifference = Long.MAX_VALUE;
		//goes from 0 to _ _ _ ... _ with n _s for all possibilities of taking each apple at each position
		for (int bitmask = 0; bitmask < (1 << n); bitmask++) {
			long basket1 = 0, basket2 = 0;
			ArrayList<Integer> basketList1 = new ArrayList<>(); //subset1
			ArrayList<Integer> basketList2 = new ArrayList<>(); //subset2
			for (int i = 0; i < n; i++) {
				if ((bitmask & (1 << i)) > 0) { //check if bitmask at position i is a 1
					basket1 += apples[i]; 
					basketList1.add(apples[i]); //if it's a 1, we put that apple into subset1
				}else {
					basket2 += apples[i];
					basketList2.add(apples[i]);
				}
			}
			System.out.println(basketList1 + " " + basketList2);
			minDifference = Math.min(minDifference, Math.abs(basket1 - basket2));
		}
		System.out.println(minDifference);
	}

}
