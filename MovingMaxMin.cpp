/*
starting at each position (0-indexed), print out the min and max of each subarray of size m
uses deque and runs in o(n) time
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, x;
deque<pair<int, int>> minq, maxq; //{value, index}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n >> m; //n elements, window size is m
  
  for (int i = 0; i < n; i++){
    cin >> x; //read in the ith element
    while (!minq.empty() && minq.back().first > x){ //get rid of all elements before i that are larger than i, this is an increasing queue, first element is always smallest
      minq.pop_back();
    }
    minq.push_back({x, i}); //push the current element into the queue
    while (!maxq.empty() && maxq.back().first < x){ //get rid of all elements before i that are smaller than i, this is a decreasing queue, first element is always largest
      maxq.pop_back();
    }
    maxq.push_back({x, i}); //push the current element into the queue
    if (i >= m - 1){ //if the current index can be the end index of the sliding window
      while (minq.front().second < i - m + 1){ //pop everything at the front that are from indices prior to the starting index of the current window (not covered by the window)
        minq.pop_front();
      }
      while (maxq.front().second < i - m + 1){
        maxq.pop_front();
      }
      printf("Min of window starting at %d is %d\nMax of window starting at %d is %d\n", i - m + 1, minq.front(), i - m + 1, maxq.front());   
    }
  }
  return 0;
}
