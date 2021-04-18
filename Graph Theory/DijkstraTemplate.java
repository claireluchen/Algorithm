package Graph;

import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;

//find shortest path in weighted graph
//stores graph in an array of arraylist, each arraylist element is a pair (distance, toNode)
//prints out shortest distance from starting node to destination node
public class DijkstraTemplate {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), m = in.nextInt(); //n nodes, m edges
		int start = in.nextInt() - 1, end = in.nextInt() - 1; //starting to destination nodes
		ArrayList<Pair>[] adj = new ArrayList[n];
		for (int i = 0; i < n; i++) adj[i] = new ArrayList<Pair>();
		for (int i = 0; i < m; i++) {
			int from = in.nextInt() - 1, to = in.nextInt() - 1, weight = in.nextInt();
			adj[from].add(new Pair(weight, to));
			adj[to].add(new Pair(weight, from));
		}
		
		PriorityQueue<Pair> q = new PriorityQueue<>();
		int[] distance = new int[n]; //distance from the starting node
		boolean[] visited = new boolean[n]; //keep track if visited
		int[] prev = new int[n]; //previous node of current node, helps to backtrack the path
		for (int i = 0; i < distance.length; i++) distance[i] = Integer.MAX_VALUE;
		q.add(new Pair(0, start)); //(distance from starting node, node)
		distance[start] = 0;
		prev[start] = -1;
				
		while (!q.isEmpty()) {
			int cur = q.poll().y; //greedy algorithm, always take the node that's closest to the previous node (lowest weight)
			if(visited[cur]) continue; //if the shortest route leads to a node we've visited, skip, pull the next shortest route
			visited[cur] = true;
			for (Pair nxt : adj[cur]) {
				int b = nxt.y, w = nxt.x; //b is the next node, w is the weight from cur to nxt (b)
				if (distance[cur] + w < distance[b]) { //compare the new distance with original distance
					//new distance is the distance from root node to the previous node plus the distance from previous node to current node
					distance[b] = distance[cur] + w;
					prev[b] = cur;
					q.add(new Pair(distance[b], b));
				}
			}
		}
		System.out.println(distance[end]); //shortest distance to end
		//prints out the path from starting to end node by backtracking with prev
		ArrayList<Integer> path = new ArrayList<>();
		for (int i = end; i != -1; i = prev[i]) {
			path.add(i);
		}
		for (int i = path.size() - 1; i >= 0; i--) System.out.print(path.get(i) + 1 + " ");
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
