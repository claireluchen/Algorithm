#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const int maxn = 2e5 + 5;

int n;
vector<int> arr[maxn];
int fa[maxn][22], depth[maxn], p[maxn], sum[maxn];

//find fa[i][0] aka the direct parent of i and keep track of the depth of the nodes assuming 1 is the root
void dfs(int cur, int prev){ 
  fa[cur][0] = prev;
  depth[cur] = depth[prev] + 1;
  for (int i : arr[cur]){
    if (i == prev) continue;
    dfs(i, cur);
  }
}

int lca(int x, int y){ //find the lowest common ancestor of nodes x and y
  if (depth[y] > depth[x]){
    int tmp = x; x = y; y = tmp;
  }
  //y is closer to root than x, move x up the chain so it is at the same depth as y
  for (int j = 20; j >= 0; j--){
    if (depth[fa[x][j]] >= depth[y]){
      x = fa[x][j];
    }
    if (x == y) return y; //if y is a direct ancestor of x, return y
  }
  //x and y are at the same depth, keep moving up till they merge at the same node (might take multiple steps like 16 + 4 + 1 -> 21)
  for (int j = 20; j >= 0; j--){
    if (fa[x][j] != fa[y][j]){
      x = fa[x][j]; y = fa[y][j];
    }
  }
  return fa[x][0];
}

void dfs2(int cur, int prev){ //sum the number of times a path has been used
  sum[cur] = p[cur];
  for (int nxt : arr[cur]){
    if (nxt == prev) continue;
    dfs2(nxt, cur);
    sum[cur] += sum[nxt];
  }
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);

  cin >> n;
  for (int i = 1; i < n; i++){
    int x, y, a, b; cin >> x >> y >> a >> b; 
    arr[x].push_back(y);
    arr[y].push_back(x);
  }

  dfs(1, 0);
  for (int i = 1; i <= 20; i++){
    for (int j = 1; j <= n; j++){
      fa[j][i] = fa[fa[j][i - 1]][i - 1];
    }
  }

  for (int i = 1; i < n; i++){
    int g = lca(i, i + 1);
    p[i]++; p[i + 1]++; p[g] -= 2;
  }

  dfs2(1, 0);
  for (int i = 1; i < n; i++){
    cout << sum[i] << endl;
  }
  return 0;
}
