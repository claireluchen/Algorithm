/*
Find the longest path of a directed, unweighted, acyclic graph.
Run DFS starting at every node.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;

int n, m, dis[maxn];
bool vis[maxn];
vector<int> adj[maxn];

int dfs(int x){
  if (vis[x]) return dis[x];
  vis[x] = true;
  for (int nxt : adj[x]){
    dis[x] = max(dis[x], 1 + dfs(nxt)); //keep track of the longest possible distance
  }
  return dis[x];
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n >> m;

  for (int i = 0; i < m; i++){
    int x, y; cin >> x >> y;
    adj[x].push_back(y);
  }
  
  int ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, dfs(i)); //trying every node as starting point
  cout << ans << endl;
  return 0;
}
