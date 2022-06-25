#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

int n, m;
vector<pair<ll, int>> adj[maxn];
ll dis[maxn];
bool vis[maxn];
priority_queue<pair<ll, int>> q;

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);

  cin >> n >> m;
  for (int i = 0; i < m; i++){
    int a, b; ll c;
    cin >> a >> b >> c;
    adj[a].push_back({c, b});
  }

  for (int i = 2; i <= n; i++) dis[i] = 0x3f3f3f3f;
  q.push({0, 1});
  while (!q.empty()){
    int cur = q.top().second; q.pop();
    if (vis[cur]) continue;
    vis[cur] = true;
    for (pair nxt : adj[cur]){
      int b = nxt.second; ll d = nxt.first;
      if (dis[b] > dis[cur] + d){
        dis[b] = dis[cur] + d;
        q.push({-dis[b], b});
      }
    }
  }

  for (int i = 1; i <= n; i++) cout << dis[i] << " ";
  return 0;
}
