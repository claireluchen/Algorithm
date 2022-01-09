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
char cnt[1 << maxn]; //keeping track of num of 1s in binary representation of each number

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
  for (int i = 1; i < (1 << n); i++){ //count the number of 1s in each number from i to 1 << n to use later
    int sum = 0;
    int temp = i;
    while (temp){
      if (temp & 1) sum++;
      temp >>= 1;
    }
    cnt[i] = sum;
  }
  f[0] = 1;
  for (int i = 0; i < n; i++){ //for each person
    for (int s = 0; s < (1 << n); s++){
      if (cnt[s] != i + 1) continue; //checking if the current bitmask, s, contains i assignments/is valid for i ppl (by checking if it has i 1s)
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
