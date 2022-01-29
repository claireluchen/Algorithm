#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e4 + 5;
const int mod = 1e9 + 7;

int n, m, dest;
vector<int> adj[maxn];
int dis[maxn];
bool vis[maxn];

void dfs(int cur, int d){
  if (vis[cur]) return;
  vis[cur] = true;
  dis[cur] = d;
  for (int nxt : adj[cur]){
    dfs(nxt, d + 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n >> m;
  for (int i = 0; i < m; i++){
    int x, y;
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  } 
  dfs(1, 0);
  cin >> dest;
  cout << dis[dest] << endl; //print distance from root node to dest, not guranteed to be the shortest distance
  
  bool connected = true;
  for (int i = 1; i <= n; i++){
    if (!vis[i]){
      connected = false;
      break;
    }
  }
  cout << (connected ? "Yes" : "No") << endl;

  return 0;
}
