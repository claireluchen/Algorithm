/*
Find the number of articulation points (cut vertex) in the graph
dfn is the discovery time of a node
low[u] is the first visited node after walking down with dfs starting at u
if the first visited node is where it came from, then that node is the cut vertex
let v be the parent node, u be its child, if low[u] >= dfn[v], then v is a cut vertex (v blocks the way for u to reach any node before v)
(if low[u] < dfn[v], then there exists a backedge where u can reach nodes in a different part of the graph without having to pass its parent)
note that for the root node, it needs to have at least two children whose low[u] >= dfn[v] for it to be the cut vertex
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;

vector<int> edge[N];
int cnt = 0; //keep track of discovery time
int dfn[N], low[N], pt[N]; //pt keeps track of the number of children of v whose low[u] >= dfn[v]

void dfs(int x, int from_p) {
	dfn[x] = low[x] = ++cnt; //first set low[x] to be the same as its discovery time

	for (int y : edge[x]) {
		if (y == from_p) continue; //if the next node is the parent of the current node, no need to visit it so skip
		if (dfn[y]) { //we've reached the first node that has already been visited
			low[x] = min(low[x], dfn[y]); //take the minimum between the current low ad the discovery time of that node
		}
		else {
			dfs(y, x); //explore the child
			low[x] = min(low[x], low[y]); //continuously update low to the minimum discovery time of the first visited node, compare between cur and low of every child
			if (x == 1 || low[y] >= dfn[x]) pt[x]++; //update pt
		}
	}
}

int main() {

	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	
	dfs(1, 0);
	pt[1]--; //since root node needs to have pt[1] >= 2, do pt[1]-- such at if pt[1] = 1 or 0, node 1 is not a cut vertex and won't be counted in the subsequent if statement

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (pt[i]) ans++;
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++) { //printing out all cut vertices
		if (pt[i]) cout << i << endl;
	}

	return 0;
}
