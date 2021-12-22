/*
Knapsack problem, each item can only be taken once.
Using a 1D array to save memory by working backwards.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 1;
ll n, cap, ans, arr[maxn];
 
int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
 
  cin >> n >> cap;
  for (int i = 0; i < n; i++){
    ll w, v; cin >> w >> v;
    for (int j = cap; j >= w; j--){
      arr[j] = max(arr[j], arr[j - w] + v);
    }
  }

  for (int i = 0; i <= cap; i++) ans = max(ans, arr[i]);
  cout << ans << endl;
  return 0;
}
