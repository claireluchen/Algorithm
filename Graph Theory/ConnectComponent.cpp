/*
given n cities and m roads between them, construct new roads so that there is a route between any two cities . find out the minimum number of roads required and determine which roads should be built 
to connect all components, c - 1 edges is needed (c being the number of existing components), then simply take one node from each component and link them
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 5;

int n, m, rep[maxn]; //n nodes, m edges, representative of each component
vector<int> adj[maxn]; //adjacency list
bool vis[maxn];

void dfs(int node){
  if (vis[node]) return;
  vis[node] = true;
  for (auto u : adj[node]){
    dfs(u);
  }
}

int count_components(){
  int cnt = 0;
  for (int i = 1; i <= n; i++){ //for each node
    if (vis[i]) continue; //if already visited, then it's already part of an existing compoenent, no need to visit it again
    rep[cnt] = i; //mark the node as the representative
    cnt++; //since the node hasn't been visited, it can be used as the root for a new component
    dfs(i); //run dfs on the node and label all nodes in the component visited
  }
  return cnt;
}

int main() {  
  cin >> n >> m;
  for (int i = 0; i < m; i++){
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b); adj[b].push_back(a);
  }
  int cnt = count_components();
  cout << cnt - 1 << "\n";
  for (int i = 1; i < cnt; i++){
    cout << rep[i - 1] << " " << rep[i] << "\n";
  }
  return 0;
}
