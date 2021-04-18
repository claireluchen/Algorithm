package Graph;

import java.util.ArrayList;
import java.util.Scanner;

public class DFSTemplate {

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
		
		dfs(1, adj, visited); //starting node, adjacency list, visited aray

	}
	
	public static void dfs(int s, ArrayList<Integer>[] adj, boolean[] visited) {
		if (visited[s]) return;
		visited[s] = true;
		System.out.print(s + " -> ");
		for (int u : adj[s]) {
			dfs(u, adj, visited);
		}
		System.out.println();

	}
}
