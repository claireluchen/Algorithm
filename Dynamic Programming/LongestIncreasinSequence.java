import java.util.Scanner;

/*
find the longest increasing subsequence in an array of n elements
(a maximum-length sequence of array elements that goes from left to right, 
and each element in the sequence is strictly larger than the previous element)

Let length(k) denote the length of the longest increasing subsequence that
ends at position k. Thus, if we calculate all values of length(k) where 0 <= k <= n - 1,
we will find out the length of the longest increasing subsequence.

To calculate a value of length(k), we should find a position i < k for which
array[i] < array[k] and length(i) is as large as possible. Then we know that
length(k) = length(i) + 1, because this is an optimal way to add array[k] to a
subsequence. However, if there is no such position i,
 */
public class LongestIncreasinSequence {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(); //n is the total number of values
		int[] numbers = new int[n];
		for (int i = 0; i < numbers.length; i++) numbers[i] = in.nextInt();
		int[] lengths = new int[n]; //longest increasing sequence at each position
		for (int k = 0; k < numbers.length; k++) {
			lengths[k] = 1;
			for (int j = 0; j < k; j++) {
				if (numbers[j] < numbers[k]) {
					lengths[k] = Math.max(lengths[k], lengths[j] + 1);
				}
			}
		}
		Arrays.sort(lengths);
		System.out.println(lengths[n - 1]);
	}

}
