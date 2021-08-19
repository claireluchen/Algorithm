/*
Find the longest palindomic substring in O(nlogn) using string hashing and binary search
Hash the string forward and backward to retrieve the hash of a substring in O(1)
Binary search for the longest substring and at each position, check if that position can be the centre/middle of a substring with the wind-span, taking O(logn) * O(n)
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 25005, base = 131, mod = 1e9+7; //assuming the maximum length of the substring is 25000

int n;
string str;
ll hsh1[maxn], hsh2[maxn], pw[maxn];

ll getHash1(int l, int r){
  return (hsh1[r] - hsh1[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}

ll getHash2(int l, int r){
  return (hsh2[r] - hsh2[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);

  cin >> str; n = str.size();
  pw[0] = 1;
  for (int i = 1; i <= n; i++){
    pw[i] = pw[i - 1] * base % mod;
    hsh1[i] = (hsh1[i - 1] * base + str[i - 1] - 'A') % mod;
    hsh2[i] = (hsh2[i - 1] * base + str[n - i] - 'A') % mod;
  }

  int low = 0, high = n, mid = (low + high) / 2, left = 0, right = 0;
  bool b = true;
  while (low <= high){
    for (int i = 1; i <= n; i++){ //iterating through each position
      int h1, h2;
      if (i - mid + 1 >= 1 && i + mid <= n){ //checking for even length substring like abba and ccddcc
        h1 = getHash1(i - mid + 1, i);
        h2 = getHash2(n - i - mid + 1, n - i);
        if (h1 == h2){ 
          if (mid == 0){ //length of palidrome is 1, just 1 letter
              left = i; right = i;
          }else{ //this current mid value works (ex: mid = 2 in abba and mid = 3 in ccddcc)
              left = i - mid + 1; right = i + mid;
              low = mid + 1; //increase the lower bound to see if a longer palindrom can be found
              b = false;
              break;    
          }
        }    
      }
      
      if (i - mid >= 1 && i + mid <= n){ //checking for odd length substring like aba and ccdcc
        h1 = getHash1(i - mid, i);
        h2 = getHash2(n - i - mid + 1, n - i + 1);
        if (h1 == h2){
          left = i - mid; right = i + mid;
          low = mid + 1;
          b = false;
          break;
        }  
      }
    }
    if (b){
      high = mid - 1;
    }
    mid = (low + high) / 2;
    b = true;
  }
  cout << right - left + 1 << endl; //print out the length of the substring
  cout << str.substring(left - 1, right - left + 1); //print out the actual substring
  return 0;
}
