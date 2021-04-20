package DynamicProgramming;
/*
Given a set of coin values coins = {c1, c2,..., ck} and a target sum of money n, 
form the sum n using as few coins as possible.
*/
import java.util.Scanner;

public class CoinProblemIterative {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(); //number of coins
		int[] coins = new int[n]; //available coin values
		for (int i = 0; i < coins.length; i++) coins[i] = in.nextInt();
		int m = in.nextInt(); //value we want to reach
		int[] minNum = new int[m + 1]; //minimum number of coins used to reach the value
		
		minNum[0] = 0;
		for (int x = 1; x <= m; x++) {
			minNum[x] = Integer.MAX_VALUE - 1;
			for (int i = 0; i < coins.length; i++) {
				if (x - coins[i] >= 0) {
					minNum[x] = Math.min(minNum[x], minNum[x - coins[i]] + 1);
				}
			}
		}
		System.out.println(minNum[m]);
	}

}
