/*
Given N flowers, each flower has a distinct height and a beauty value.
The flowers have to be arranged in a way such at their heights are strictly increasing and the total beauty is maximized.

Naive dp solution: for every flower, find a flower before it with height less than the current flower and total beauty greater than the current, "updated" one
This could take O(n^2) time and would TLE
for (int i = 1; i <= n; i++){
   for (int j = 1; j < i; j++){
     if (h[j] < h[i] && f[j] > f[i]){
       f[i] = f[j];
     }
   }
   f[i] += a[i];
   ans = max(ans, f[i]);
 }
 
 Instead, use a segment tree to quickly find the max height between any interval.
 The bottom of the tree stores the max beauty at each height, with index value = height
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;
 
int n, h[maxn];
ll a[maxn], f[maxn], fMax[3 * maxn];
 
ll getFMax(int x,int l,int r,int ll,int rr){ //max value from ll to rr
  if (ll > rr) return 0;
  if (l >= ll && r <= rr){
    return fMax[x];
  }
  int mid = (l + r) >> 1;
  long long lsum = 0,rsum = 0;
  if (ll <= mid) lsum = getFMax(x<<1,l,mid,ll,rr);
  if (rr > mid) rsum = getFMax(x<<1|1,mid+1,r,ll,rr);
  return max(lsum, rsum);
}
 
void update(int x, int l, int r, int t, ll v){
  if (l == r){
    fMax[x] = v;
    return;
  }
  int mid = (l + r) / 2;
  if (t <= mid){
    update(x << 1, l, mid, t, v);
  }else{
    update(x << 1 | 1, mid + 1, r, t, v);
  }
  fMax[x] = max(fMax[x << 1], fMax[x << 1 | 1]);
}
 
int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> h[i];
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++){
    f[i] = getFMax(1, 1, n, 1, h[i] - 1) + a[i]; //get the max beauty achieved for a valid list of flower with height less than the current one and then add the beauty of the current one
    update(1, 1, n, h[i], f[i]); //update the tree with the new total beauty achieved for the current height
  }
  cout << getFMax(1, 1, n, 1, n) << endl;
  return 0;
}
