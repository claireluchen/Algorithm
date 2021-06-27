/*
kruskal's algorithm
Each node of the graph initially belongs to a separate component. 
When an edge is added to the tree, the two components which the nodes belong are joined. 
When all nodes belong to the same component, a MST is formed.
Sort the edges and greedily take on the smallest one
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e9 + 9;
const int MAXN = 1e5 + 5;
int link[MAXN]; //stores the previous element it's chained to, stores itself if the element is the representative
int ssize[MAXN]; //for each representative, the size of the corresponding set

int find(int x) { //returns the representative of x
  while (x != link[x]) x = link[x];
  return x;
}

bool same(int a, int b) { //check if nodes a and b belong to the same set
  return find(a) == find(b); //if they have the same representative, then they're in the same set
}

void unite(int a, int b) { //unite the sets that contain node a and b
  a = find(a); //find the representative of a
  b = find(b); //find the representative of b
  //join the smaller set to the larger set
  if (ssize[a] < ssize[b]){
    ssize[b] += ssize[a];
    link[a] = b;
  }else{
    ssize[a] += ssize[b];
    link[b] = a;
  }
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> list; //<weight, (node a, node b)>
    
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
