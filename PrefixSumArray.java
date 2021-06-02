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
