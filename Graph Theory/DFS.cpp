#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

int n, m; //n nodes, m edges
vector<int> adj[maxn];
bool vis[maxn];

void dfs(int cur){
  for (int nxt : adj[cur]){
    if (vis[nxt]) continue;
    vis[nxt] = true;
    dfs(nxt);
  }
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n >> m;
  for (int i = 0; i < m; i++){
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1);
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
