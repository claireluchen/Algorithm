import java.util.*;
/*
Generating all subsets recursively
The generation begins when the function is called with parameter 0
Subsets of {0,1,2} are {}, {0}, {1}, {2}, {0,1}, {0,2}, {1,2} and {0,1,2}
*/
public class Main{
  static int n;
  static int[] values;
  static ArrayList<ArrayList<Integer>> subsets; 
  static ArrayList<Integer> temp;

	public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    n = in.nextInt(); //number of items we have to generate subsets
    values = new int[n]; //read in the numbers
    for (int i  = 0; i < values.length; i++){
      values[i] = in.nextInt();
    }
    subsets = new ArrayList<>();
    temp = new ArrayList<>();
    recur(0);
    System.out.println(subsets); //print out all subsets, such as [[], [0], [1], [2], [0, 1], [0, 2], [1, 2], [0, 1, 2]]
  }

  public static void recur(int k){
    if (k == n){
      ArrayList<Integer> copy = new ArrayList<>(); //make a copy of our temp and store it into the subsets ArrayList
      for (int i : temp){
        copy.add(i);
      }
      subsets.add(copy);
      return;
    }else{
      recur(k + 1);
      temp.add(values[k]);
      recur(k + 1);
      temp.remove(temp.size() - 1);
    }
  }
}
