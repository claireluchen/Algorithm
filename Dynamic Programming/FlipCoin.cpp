/*
Given n coins and their probability of landing on heads, calculate the probability when all coins are flipped and more than half of them land on heads.
Construct a 2D array, where arr[i][j] means the probability after tossing first i coins and receiving at least j heads.
Default arr[i][0] to 1, arr[0][i] to 0, arr[0][0] to 1
Then, arr[i][j] = arr[i - 1][j - 1] * heads[i] + arr[i - 1][j] * tail[i]
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e3 + 5;

int n, required;

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n;
  required = n / 2 + 1;
  double head[n + 1], tail[n + 1], arr[n + 1][n + 1];
  arr[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> head[i];
    tail[i] = 1 - head[i];
    arr[i][0] = 1;
    arr[0][i] = 0;
  }
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= required; j++){
      arr[i][j] = arr[i - 1][j - 1] * head[i] + arr[i - 1][j] * tail[i];
    }
  }
  cout << fixed << setprecision(10) << arr[n][required] << endl;
  return 0;
}
