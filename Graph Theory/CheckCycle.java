package Graph;

import java.util.ArrayList;
import java.util.Scanner;

public class CheckCycle {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), m  = in.nextInt(); //n nodes, m edges
		ArrayList<Integer>[] adj = new ArrayList[n + 1]; //store graph in adjacency list
		for (int i = 0; i < adj.length; i++) adj[i] = new ArrayList<>();
		for (int i = 0; i < m; i++) {
			int from = in.nextInt(), to = in.nextInt();
			adj[from].add(to); adj[to].add(from);
		}
		boolean[] visited = new boolean[n + 1];
		boolean[] beingVisited = new boolean[n + 1];
		if (hasCycle(1, adj, visited, beingVisited)) System.out.println("contains cycle");
		else System.out.println("no cycle");
	}
	
	public static boolean hasCycle(int s, ArrayList<Integer>[] adj, boolean[] visited, boolean[] beingVisited) {
		beingVisited[s] = true;
		for (int neighbour : adj[s]) {
			if (beingVisited[neighbour]) return true;
			else if (!visited[neighbour] && hasCycle(neighbour, adj, visited, beingVisited)) return true;
		}
		
		beingVisited[s] = false;
		visited[s] = true;
		return false;
	}
}
