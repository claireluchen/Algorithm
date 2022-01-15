/*
  1          5
 / \         |
2   3        6
|
4
parent[4] = 2, parent[2] = 1, parent[3] = 1, parent[1] = 1, parent[6] = 5, parent[5] = 5
sz[1] = 4, sz[5] = 2
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m; //n nodes from 1 to n, m edges
int parent[maxn], sz[maxn];

int root(int x){ //O(n^2)
  if (parent[x] == x){
    return x;
  }else{
    return root(parent[x]);
  }
}

int root2(int x){ //O(log n), path compression
  if (parent[x] == x){
    return x;
  }else{
    parent[x] = root2(parent[x]);
    return parent[x];
  }
}

void merge(int x, int y){ //merge set containing x with set containing y
  int xRoot = root(x);
  int yRoot = root(y);
  if (sz[xRoot] >= sz[yRoot]){
    parent[yRoot] = xRoot;
    sz[xRoot] += sz[yRoot];
  }else{
    parent[xRoot] = yRoot;
    sz[yRoot] += sz[xRoot];
  }
}

bool same(int x, int y){ //check if x and y belong to the same set
  return root(x) == root(y);
}

void initializeSize(){ //initialize the size of each set with i being the root
  for (int i = n; i > 0; i--){ //assumes all children node have higher indexing value than root
    if (parent[i] != i) sz[parent[i]] += sz[i];
  }
}

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); cout.tie(0);
  
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    sz[i] = 1;
  }
  for (int i = 0; i < m; i++){
    int x, y; cin >> x >> y; //x is the parent of y
    parent[y] = x;
  }
  initializeSize(); //initialize the size of the sets starting at each node
cout << sz[1] << " " << sz[5] << endl;

  cout << "Get the root of: " << endl;
  int r; cin >> r;
  cout << root(r) << endl;

  cout << "Merge set containing x with set containing y: " << endl;
  int x, y; cin >> x >> y;
  merge(x, y);
  cout << "Get the root of: " << endl;
  cin >> r;
  cout << root(r) << endl;

  cout << "Check if x and y belong to the same union: " << endl;
  cin >> x >> y;
  cout << same(x, y) << endl;
  cout << sz[1] << endl;
  return 0;
}
