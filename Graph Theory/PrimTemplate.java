package Graph;

import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;

import Graph.DijkstraTemplate.Pair;

/*
Prim's minimum spanning tree
A spanning tree of a graph consists of all nodes of the graph and some of the
edges of the graph so that there is a path between any two nodes. Like trees
in general, spanning trees are connected and acyclic.
A minimum spanning tree is a spanning tree whose weight is as small as possible.

Prim's algorithm resembles Dijkstra's algorithm. The difference is that Dijkstra's algorithm 
always selects an edge whose distance from the starting node is minimum, but Prim's algorithm 
simply selects the minimum weight edge that adds a new node to the tree
 */
public class PrimTemplate {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), m = in.nextInt(); //n nodes, m edges
		ArrayList<Pair>[] adj = new ArrayList[n];
		for (int i = 0; i < n; i++) adj[i] = new ArrayList<Pair>();
		for (int i = 0; i < m; i++) {
			int from = in.nextInt() - 1, to = in.nextInt() - 1, weight = in.nextInt();
			adj[from].add(new Pair(weight, to));
			adj[to].add(new Pair(weight, from));
		}
		
		int totalWeight = 0;
		PriorityQueue<Pair> q = new PriorityQueue<>();
		boolean[] visited = new boolean[n];
		q.add(new Pair(0, 0));
		ArrayList<Integer> list = new ArrayList<>();
		
		while (!q.isEmpty()) {
			Pair temp = q.poll(); //greedy algorithm, always take the node that's closest to the previous node (lowest weight)
			int curWeight = temp.x;
			int cur = temp.y; 
			if(visited[cur]) continue; //if the shortest route leads to a node we've visited, skip, pull the next shortest route
			visited[cur] = true;
			totalWeight += curWeight;
			list.add(cur);
			for (Pair nxt : adj[cur]) {
				int b = nxt.y, w = nxt.x; //b is the next node, w is the weight from cur to nxt (b)
				q.add(new Pair(w, b));
			}
		}
		System.out.println(list);
		System.out.println(totalWeight);
	}
	
	static class Pair implements Comparable<Pair>{
	    int x, y;
	    public Pair(int x, int y){
	    	this.x = x; this.y = y;
	    }
	   
	    @Override
	    public int compareTo(Pair obj) {
	    	if (x < ((Pair) obj).x) return -1;
	    	if (x > ((Pair) obj).x) return 1;
	    	return 0;
	    }
	    
	    @Override
	    public boolean equals(Object obj){
	    	if (obj instanceof Pair && x == ((Pair) obj).x && y == ((Pair) obj).y)
	    		return true;
	    	else return false;
	    }
	   
	    @Override
	    public int hashCode(){
	    	int result = x / 11 + y;
	    	return result;
	    }
		
	}
}
