package DynamicProgramming;

import java.util.Scanner;

/*
A version of the coin problem where our task is to
calculate the total number of ways to produce a sum x using the coins
Ex: coins = {1, 3, 4} and m = 5, our answer would be 6
1, 1, 1, 1, 1
1, 1, 3
1, 3, 1
3, 1, 1
1, 4
4, 1
For example, if coins = {1,3,4}, then solve(5) = 6 and the recursive formula is
solve(x) =solve(x-1) + solve(x-3) + solve(x-4)
if x < 0, solve(x) = 0 //no solution
if x == 0, solve(x) = 1
if x > 0, solve(x) += solve(x - c) where c is in coins
 */
public class CoinProblemCount {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] coins = new int[n];
		for (int i = 0; i < n; i++) coins[i] = in.nextInt();
		int m = in.nextInt();
		int[] ways = new int[m + 1]; //number of ways to reach that sum

		ways[0] = 1;
		for (int i = 1; i < ways.length; i++) {
			for (int j = 0; j < coins.length; j++) {
				if (i - coins[j] >= 0)
					ways[i] += ways[i - coins[j]];
			}
		}
		System.out.println(ways[m]);
	}

}
