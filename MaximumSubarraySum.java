//find the maximum sum of values in a contiguous, nonempty subarray
//let min[i] store the minimum possible sum value of elements up until i
//the maximum sum at j is psa[j] - min[j] and the maximum sum of each possible right bound is the maximum sum of the entire array
//the 2 for loops can also be easily modified and combined
public class Main{
  public static void main(String[] args) throws IOException{
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int[] psa = new int[n + 1];
    int[] min = new int[n + 1]; min[0] = Integer.MAX_VALUE;
    for (int i = 1; i <= n; i++){
      int num = readInt();
      psa[i] = psa[i - 1] + num;
      min[i] = Math.min(min[i - 1], psa[i]);
    }
    
    for (int i = 1; i < psa.length; i++){
      psa[i] = psa[i] - min[i];
    }
    
    Arrays.sort(psa);
    System.out.println(psa[n]);    
  }
}
