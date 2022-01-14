/*
There are N slimes lining up in a row. The size of the i-th slime is ai.
Repeatedly perform the following operations until there is only one slime:
Choose two adjacent slimes, and combine them into a new slime. The new slime has a size of x+y, where x and y are the sizes of the slimes before combining them. 
Here, a cost of x+y is incurred. The positional relationship of the slimes does not change while combining slimes.
Find the minimum possible total cost incurred.
Sample input: 
4
10 20 30 40
Sample output: 190

dp[i][j] represents the minimum cost of combinning slimes from i to j, inclusive
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 405;
const int mod = 1e9 + 7;
 
int n;
ll psa[maxn], arr[maxn], dp[maxn][maxn];
int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> arr[i];
    psa[i] = psa[i - 1] + arr[i];
  }
  memset(dp, 0x3f3f3f3f, sizeof(dp));
  for (int i = 1; i + 1 <= n; i++){
    dp[i][i + 1] = arr[i] + arr[i + 1];
  }
  for (int i = 1; i <= n; i++){
    dp[i][i] = 0;
  }
  for (int i = n; i >= 1; i--){
    for (int j = i + 2; j <= n; j++){
      ll curMin = 0x3f3f3f3f3f3f3f3f;
      for (int k = i; k < j; k++){ //check every possible point of combining two piles 
        curMin = min(curMin, dp[i][k] + dp[k + 1][j]);
      }
      dp[i][j] = curMin + psa[j] - psa[i - 1];
    }
  }
  cout << dp[1][n] << endl;
  return 0;
}
