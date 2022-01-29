#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e4 + 5;
const int mod = 1e9 + 7;

int n, m, dest;
vector<int> adj[maxn];
int dis[maxn];
bool vis[maxn];

void dfs(int cur, int d){ //current node, distance of current node from root
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
  
  bool connected = true; //determine whether whole graph is connected
  for (int i = 1; i <= n; i++){
    if (!vis[i]){
      connected = false;
      break;
    }
  }
  cout << (connected ? "Yes" : "No") << endl;

  //find the max distance from a root
  //can be used to find diameter of tree. if u is the farthest node from v, run dfs using u as root then find the fatheest node from u, call it w
  //then diameter has endpoints v and w
  //to find the radius, for every node on the diameter called x, take the max of (all min(dis of x to v, dis of x to w))
  int maxDis = -1, maxDisNode = 0;
  for (int i = 1; i <= n; i++){ 
    if (maxDis < dis[i]){
      maxDis = dis[i];
      maxDisNode = i;
    }
  }
  cout << maxDisNode << ": " << maxDis << endl;
  
  return 0;
}
