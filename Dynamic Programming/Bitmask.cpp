/*
Input:
The first line contains an integer, the number of Jimmy Bonds and missions.
The jth integer on the ith line is the probability that ith Jimmy Bond would successfully complete jth mission, given as a percentage.
Output:
Output the maximum probability of Jimmy Bonds successfully completing all the missions, as a percentage. Each Jimmy Bonds can only take one mission.

Similar problem: https://atcoder.jp/contests/dp/submissions/28097820
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 20;
const int mod = 1e9 + 7;
 
int n;
double arr[maxn][maxn];
double f[1 << maxn]; //bitmask dp

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      cin >> arr[i][j];
      arr[i][j] /= 100;
    }
  }

  f[0] = 1;
  for (int i = 0; i < n; i++){ //for each person
    for (int s = 0; s < (1 << n); s++){
     //__builtin_popcount(s) gives the number of 1s in s
      if (__builtin_popcount(s) != i + 1) continue; //checking if the current bitmask, s, contains i assignments/is valid for i ppl (by checking if it has i 1s)
      f[s] = 0;
      for (int j = 0; j < n; j++){ 
        if ((s & (1 << j)) == 0) continue; //checking whether jth mission is assigned
        //assume jth mission is assigned to ith person and have other ppl taking the rest of the assigned missions
        //check if the probability becomes greater
        f[s] = max(f[s], f[s - (1 << j)] * arr[i][j]); 
      }
    }
  }
  cout << fixed << setprecision(10) << f[(1 << n) - 1] * 100; //print the max probability when all missions are assigned (n 1s)
  return 0;
}
