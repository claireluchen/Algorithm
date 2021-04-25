import java.util.*;
import java.io.*;
/*
Weiwei is given a multiset of N integers. 
Out of all N integers, only one appeared an odd number of times, 
and all others have appeared an even number of times. 
What is the value of this integer?
a ^ a = 0
a ^ 0 = a

Sample input:
3
2
2
1
Output:
1

2 -> 0 1 0
1 -> 0 0 1

   0 1 0
^  0 1 0
-> 0 0 0
^  0 0 1
-> 0 0 1, and 1 is the answer
when a number appears twice, it can always get "cancelled" out by itself and become 0 at each bit position. Only the number that appears an odd number of time will not be able to cancell itself and will be remained after performing ^
*/
public class Main {
  static StringTokenizer st;
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	static String next () throws IOException {
	   	while (st == null || !st.hasMoreTokens())
	   		st = new StringTokenizer(br.readLine().trim());
	    return st.nextToken();
	}
	static int readInt () throws IOException {
		return Integer.parseInt(next());
	}

  public static void main(String[] args) throws IOException{
    int temp = 0;
    int n = readInt();
    for (int i = 0; i < n; i++) temp ^= readInt();
    System.out.println(temp);
	}
}
