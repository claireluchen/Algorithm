package DynamicProgramming;
import java.util.*;
/*
Given a set of coin values coins = {c1, c2, ..., ck} and a target sum of money n,
form the sum n using as few coins as possible

The idea is to focus on the first coin that we choose for the sum. 
For example, in the above scenario, the first coin can be either 1, 3 or 4. 
Let n be 10. If we first choose coin 1, the remaining task is to form the sum 9 using
the minimum number of coins, which is a subproblem of the original problem.
Of course, the same applies to coins 3 and 4. Thus, we can use the following
recursive formula to calculate the minimum number of coins:
solve(x) = min(solve(x-1)+1,
			solve(x-3)+1,
			solve(x-4)+1)
 */
public class CoinProblemRecursion {
	static int[] coins; //store coin values
	static int[] minNum; //minimum number of coins used to reach the value
	static boolean[] ready; //keep track if we've already calculated the minimum number of coins used
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int numOfCoins = in.nextInt();
		coins = new int[numOfCoins];
		for (int i = 0; i < coins.length; i++) {
			coins[i] = in.nextInt();
		}
		int n = in.nextInt(); //total money we aim for
		minNum = new int[n + 1];
		ready = new boolean[n + 1];
		System.out.println(solve(n));
		
	}
	public static int solve(int x) {
		if (x < 0) return Integer.MAX_VALUE - 1;
		if(x == 0) return 0;
		if (ready[x]) return minNum[x]; //memoization
		int best = Integer.MAX_VALUE;
		for (int i = 0; i < coins.length; i++) {
			best = Math.min(best, solve(x - coins[i]) + 1);
		}
		minNum[x] = best;
		ready[x] = true;
		return minNum[x];
	}
}
