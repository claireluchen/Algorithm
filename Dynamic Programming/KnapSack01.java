import java.util.*;
import java.io.*;
/*
Choosing a subset of items such that we maximize their total value, 
and their total weight does not exceed the capacity of the container

Print out the maximum value
*/
public class Main{
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
    int numOfItems = readInt();
    int[] weight = new int[numOfItems];
    int[] value = new int[numOfItems];
    for (int i = 0; i < numOfItems; i++){
      weight[i] = readInt(); value[i] = readInt();
    }
    int maxAllowed = readInt();
    int[][] array = new int[numOfItems][maxAllowed + 1];
    for (int i = 0; i <= maxAllowed; i++){ //get the first row of the 2d array
      if (weight[0] <= i){
        array[0][i] = value[0];
      }
    }
    for (int i = 1; i < numOfItems; i++){
      for (int j = 1; j <= maxAllowed; j++){
        if (weight[i] <= j){
          array[i][j] = Math.max(array[i - 1][j], value[i] + array[i - 1][j - weight[i]]);
        }else{
          array[i][j] = array[i - 1][j];
        }
      }
    }

    System.out.println(array[numOfItems - 1][maxAllowed]);
	}
}
