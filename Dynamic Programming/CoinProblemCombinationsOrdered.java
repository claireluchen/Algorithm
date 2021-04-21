/*
Consider a money system consisting of n coins. Each coin has a positive integer value. 
Calculate the number of distinct ordered ways you can produce a money sum x using the available coins.

For example, if the coins are {2,3,5} and the desired sum is 9, there are 3 ways:
2+2+5
3+3+3
2+2+2+3
*/
public class Main{
  public static void main(String[] args) throws IOException{
    int MOD = 1000000007;
    Scanner in = new Scanner(System.in);
		int n = in.nextInt(); //n coins
    int m = in.nextInt(); //m is the desired sum
		int[] coins = new int[n];
		for (int i = 0; i < n; i++) coins[i] = in.nextInt(); //fill the coin array with coin values
		int[] ways = new int[m + 1]; //number of ways to reach that sum

		ways[0] = 1;
    //"inside out" compared to the unordered combination
    //instead of for each weight (on the outer loop), we iterate through the coin values (on the inner loop) to determine the number of ways
    //we do: for each coin value, iterate through the weight to see if that weight can use the current coin
    //this makes it impossible to create two combinations with the same coins ordered differently because we update the weight in the order we iterate through the coins
		for (int i = 0; i < coins.length; i++) { //for each coin, see if we can use it at each weight
			for (int weight= 0; weight < ways.length; weight++) { //see if the coin can be used in this current weight
				if (weight - coins[i] >= 0)
					ways[weight] += ways[weight- coins[i]];
          ways[weight] %= MOD;
			}
		}
		System.out.println(ways[m]);
  }
}
