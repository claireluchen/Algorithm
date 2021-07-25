/*
given a histogram of width n, find the maximum rectangle histogram that can be formed
ans = 10
observe that to form the max histogram, the complete height of at least one bar will be included
thus, for each bar, find the left-most limit and right-most limit using a stack
h = [3, 5, 2, 4, 5]
l = [0, 1, 0, 3, 4] (stores the indices of bars)
r = [1, 1, 4, 4, 4]
area of each rectangle = (l - r + 1) * h
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e5 + 5;

int n, h[maxn], l[maxn], r[maxn];
stack<int> st1, st2;

int main() {  
  cin >> n;
  for (int i = 0; i < n; i++) cin >> h[i];
  for (int i = 0; i < n; i++){ //find the left limit
    while(!st1.empty() && h[st1.top()] >= h[i]){
      st1.pop();
    }
    l[i] = st1.empty() ? 0 : st1.top() + 1;
    st1.push(i);
  }
  for (int i = n - 1; i >= 0; i--){ //find the right limit
    while (!st2.empty() && h[st2.top()] >= h[i]){
      st2.pop();
    }
    r[i] = st2.empty() ? n - 1 : st2.top() - 1;
    st2.push(i);
  }

  int ans = 0;
  for (int i = 0; i < n; i++){
    ans = max(ans, h[i] * (r[i] - l[i] + 1));
  }
  cout << ans << endl;
  return 0;
}
