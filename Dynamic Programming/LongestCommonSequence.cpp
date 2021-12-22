/*
Given strings s and t, find one longest string that is a subsequence of both s and t.
A subsequence of a string x is the string obtained by removing zero or more characters from x and concatenating the remaining characters without changing the order.
Turn this into a grid dp: https://usaco.guide/gold/paths-grids?lang=cpp
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3001;

string s, t;
int arr[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);

  cin >> s >> t;
  for (int i = 0; i <= s.size(); i++){ //similar to a grid dp
    for (int j = 0; j <= t.size(); j++){
      if (i == 0 || j == 0) arr[i][j] = 0;
      else if (s[i - 1] == t[j - 1]) arr[i][j] = arr[i - 1][j - 1] + 1;
      else arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
    }
  }
  
  string str = ""; //trace the letters used in the longest common sequence, going backwards
  for (int i = s.size(), j = t.size(); i > 0 && j > 0;){
    if (s[i - 1] == t[j - 1]){
      str += s[i - 1];
      i--; j--;
    }else if (arr[i - 1][j] > arr[i][j - 1]) i--;
    else j--;
  }
  reverse(str.begin(), str.end());
  cout << str << endl; //the string
  cout << arr[s.size()][t.size()]<< endl; //the length of the sequence
  return 0;
}
