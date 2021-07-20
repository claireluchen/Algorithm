//get the size of the maximum rectangle that can be formed in a histogram
/*
Slightly modified GeeksForGeeks algorithm
1) Let hist[] be the histogram, n be the width of the histogram, w be the maximum width of the rectangle allowed. Create an empty stack.
2) Start from first bar, and do following for every bar ‘hist[i]’ where ‘i’ varies from 0 to n-1. 
  a) If stack is empty or hist[i] is higher than the bar at top of stack, then push ‘i’ to stack. 
  b) If this bar is smaller than the top of stack, then keep removing the top of stack while top of the stack is greater. Let the removed bar be hist[tp]. 
  Calculate area of rectangle with hist[tp] as smallest bar. For hist[tp], the ‘left index’ is previous (previous to tp) item in stack and ‘right index’ is ‘i’ (current index).
3) If the stack is not empty, then one by one remove all bars from stack and do step 2.b for every removed bar.
*/
public class Main{
  static int getMaxArea(int hist[], int n, int w){
    Stack<Integer> s = new Stack<>();
         
    int maxArea = 0;
    int tp, topArea; 
      
    int i = 0;
    while (i < n){
      if (s.empty() || hist[s.peek()] <= hist[i]){
        s.push(i++);
      }else{
        tp = s.pop();
        topArea = hist[tp] * Math.min(w, s.empty() ? i : i - s.peek() - 1);
        maxArea = Math.max(maxArea, topArea);
      }
    }

    while (!s.empty()){
      tp = s.pop();
      topArea = hist[tp] * Math.min(w, s.empty() ? i : i - s.peek() - 1);
      maxArea = Math.max(maxArea, topArea);
    }
      
    return maxArea;
  }
}
