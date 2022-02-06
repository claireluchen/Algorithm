/*
if n were too big, only store points where changes happen in a vector
ex for diff array: vt.push_back({a, 1}) to increment values starting at a by 1, then ({b, -1}) to decrement values starting at b by 1
*/
public class Main{
  public static void main(String[] args) throws IOException{
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int[] psa = new int[n];
    psa[0] = readInt();
    for (int i = 1; i < psa.length; i++){
      psa[i] = psa[i - 1] + readInt();
    }
    
    //sum[a, b] = sum[0, b] - sum[0, a - 1]
    int a = in.nextInt(), b = in.nextInt(), sum = 0;
    if (a == 0) sum = psa[b];
    else sum = psa[b] - psa[a - 1];
    System.out.println(sum);
  }
}
