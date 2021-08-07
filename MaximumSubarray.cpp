#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 5;

int n, arr[maxn], maxSum, curSum; //assuming answer >= 0

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n; //n elements, negative values are allowed
  for (int i = 0; i < n; i++) cin >> arr[i];
  for (int i = 0; i < n; i++){
    curSum += arr[i]; //add the current value to the previous group
    if (curSum < arr[i]) curSum = arr[i]; //if the resulting value is less than the current value, start a new subarray with the current value
    maxSum = max(maxSum, curSum); //update the maximum value of the subarray sum so far
  }
  cout << maxSum << endl;

  return 0;
}
