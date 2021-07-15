/*
given an array of integers, find the next greater value for each number
input:  2, 4, 1, 2, 2, 5, 1
output: 4, 5, 2, 5, 5, -1, -1
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int n;
int arr[maxn], ans[maxn];
stack<int> s;

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++){
    cin >> arr[i];
  }
  
  //use a monotonic stack, start working from the far right of the array
  for (int i = n - 1; i >= 0; i--){
    while (!s.empty() && s.top() <= arr[i]){
      s.pop();
    }
    ans[i] = s.empty() ? -1 : s.top();
    s.push(arr[i]);
  }
  
  for (int i = 0; i < n; i++){
    cout << ans[i] << " ";
  }
  return 0;
}
