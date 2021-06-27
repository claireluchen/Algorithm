#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e9 + 9;
const int MAXN = 1e5 + 5;
int link[MAXN];
int ssize[MAXN];

int find(int x) {
  while (x != link[x]) x = link[x];
  return x;
}

bool same(int a, int b) {
  return find(a) == find(b);
}

void unite(int a, int b) {
  a = find(a);
  b = find(b);
  if (ssize[a] < ssize[b]) swap(a,b);
  ssize[a] += ssize[b];
  link[b] = a;
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> list;
    
    for (int i = 0; i < m; i++){
      int a, b, w;
      cin >> a >> b >> w;
      list.push_back(pair(w, pair(a, b)));
    }
    sort(list.begin(), list.end());
    
    for (int i = 1; i <= n; i++) {
      link[i] = i;
      ssize[i] = 1;
    }

    int sum = 0;
    for (int i = 0; i < list.size(); i++){
      int a = list.at(i).second.first, b = list.at(i).second.second;
      if (!same(a, b)){
        sum += list.at(i).first;
        unite(a, b);
      }
    }
    cout << sum << endl;
}
