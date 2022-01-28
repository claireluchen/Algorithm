#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 5005;
const int mod = 1e9 + 7;

int n;

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  int l = 0, r = n, mid;
  while(l < r){
    mid = (l + r) / 2;
    if (ok(mid)){ //if mid works, search in lower half, including mid
      r = mid;
    }else{ //if mid does not work, search in upper half, excluding mid
      l = mid + 1;
    }
  }
  cout << l << endl; //loop breaks when l == r, guranteed to work since r = mid only when mid is valid
  return 0;
}
