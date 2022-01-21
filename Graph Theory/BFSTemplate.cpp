#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

int n, m;
vector<int> adj[maxn];
int dist[maxn];
bool vis[maxn];

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n >> m; //n nodes, m edges
  for (int i = 0; i < m; i++){
    int x, y; cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }  
  int start; cin >> start;
  queue<int> q;
  vis[start] = true;
  dist[start] = 0;
  q.push(start);

  while (!q.empty()){
    int cur = q.front(); q.pop();
    for (int nxt : adj[cur]){
      if (!vis[nxt]){
        q.push(nxt);
        dist[nxt] = dist[cur] + 1;
        vis[nxt] = true;
      }
    }
  } 

  int end; cin >> end;
  cout << dist[end] << endl;

  return 0;
}
