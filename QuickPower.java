/*
calculate 5 ^ 10
if we write 10 in binary -> 1010
5 ^ 10 = (5 ^ 8) * (5 ^ 2) = (5 ^ (2 ^ 3)) * (5 ^ (2 ^ 1))
whenever we see a 1 in the binary form of the exponent, we need to multiply base ^ (2 ^ position of the 1)
*/
import java.util.Scanner;

public class Main {
  private static final int MOD = 998244353;
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);	
    long base = in.nextLong(), expo = in.nextLong();
    System.out.println(pow(base, expo));
  }
  
  public static long pow(long b, long e){ //O(log n)
    b %= MOD;
    long ans = 1;
    while (e > 0){
      if ((e & 1) == 1){
        ans *= b;
      }
      e >>= 1; //divide exponent by 2
      b *= b; //raise base to b^2
      b %= MOD; //mod everything to prevent overflow
      ans %= MOD;
    }
    return ans;
  }
}
