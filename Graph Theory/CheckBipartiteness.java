package Graph;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class CheckBipartiteness {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), m = in.nextInt(); //n nodes, m edges
		//create an array that contains ArrayList of Integer
		List<Integer>[] adj = new ArrayList[n + 1]; //adjacency list
		for (int i = 0; i < adj.length; i++) {
			adj[i] = new ArrayList<>();
		}
		int start = in.nextInt(); //starting node
		for (int i = 1; i <= m; i++) {
			int u = in.nextInt(), v = in.nextInt();
			adj[u].add(v);
			adj[v].add(u);
		}
		
		Queue<Integer> q = new LinkedList();
		int[] dis = new int[n + 1]; //shortest distance from the starting node
		int[] pre = new int[n + 1]; //keep track of the node previously visited
		boolean[] vis = new boolean[n + 1]; //keep track if visited
		
		int[] black = new int[n + 1]; //each node can be either black (1) or white (2)
		
		q.add(start); //push the starting node into the queue
		vis[start] = true; //mark the starting node visited
		dis[start] = 0; //distance from starting node is 0
		pre[start] = -1; //no previously visited since it's the starting node
		black[start] = 1; //set starting node to black

		while (!q.isEmpty()) {
			int cur = q.poll(); //get the head of the queue
			for (int nxt : adj[cur]) { //get the places the previous node leads to
				if (black[nxt] == 0) {
					if (black[cur] == 1) black[nxt] = 2;
					else black[nxt] = 1;
				}else if (black[cur] == black[nxt]){
					System.out.println("can't be bipartited"); return;
				}
				if (!vis[nxt]) { //if not visited
					q.add(nxt); //add the newly discovered node to the queue
					vis[nxt] = true; //mark the node visited
					pre[nxt] = cur; //mark down the previously visited node of the current node
					dis[nxt] = dis[cur] + 1; //distance from the starting house, which is one more step than the previous node
					
				}
			}
		}		
		
		System.out.println("Can be bipartited");

	}

}
