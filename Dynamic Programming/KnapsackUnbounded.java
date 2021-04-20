import java.util.*;
/*
unbounded knapsack: each item can be taken several times
set of items
- weight
- value
take items so that
- totel value is maximized
- total weight <= given limit
print maximum value

maxArray stores the max possible value at i weight

weight: 3   4   2  6
value:  14  16  9  30
capacity = 10
maxArray 0 1 2 3  4  5  6  7  8  9  10
value    0 0 9 14 18 23 30 32 39 44 48
*/

public class KnapsackProblem {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    
    int numOfItems = in.nextInt();
    int[] weight = new int[numOfItems];
    int[] value = new int[numOfItems];
    for (int i = 0; i < numOfItems; i++){
      weight[i] = in.nextInt();
      value[i] = in.nextInt();
    }
    int capacity = in.nextInt();
    int[] maxArray = new int[capacity + 1];

    for (int i = 1; i < maxArray.length; i++){
      for (int j = 0; j < numOfItems; j++){
    	  //for the object with value[j] to be chosen, the weight[j] has to be less than i
        if (weight[j] <= i){
          maxArray[i] = Math.max(maxArray[i], maxArray[i - weight[j]] + value[j]);
        }
      }
    }   
    System.out.println(maxArray[capacity]);
    in.close();
    
  }

}
