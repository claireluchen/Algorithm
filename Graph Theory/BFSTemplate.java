import java.io.*;
import java.util.*;

public class BFSTemplate {
	static StringTokenizer st;
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
  	static String next () throws IOException {
		while (st == null || !st.hasMoreTokens())
      			st = new StringTokenizer(br.readLine().trim());
	  	return st.nextToken();
	}
	static int readInt () throws IOException {
		return Integer.parseInt(next());
	}
		  
	public static void main(String[] args) throws IOException {
		int n = readInt(), m = readInt(); //n nodes, m edges
		//create an array that contains ArrayList of Integer
		List<Integer>[] adj = new ArrayList[n + 1]; //adjacency list
		for (int i = 0; i < adj.length; i++) {
			adj[i] = new ArrayList<>();
		}
		int start = readInt(), end = readInt(); //starting node to destination node
		for (int i = 1; i <= m; i++) {
			int u = readInt(), v = readInt();
			adj[u].add(v);
			adj[v].add(u);
		}
		
		Queue<Integer> q = new LinkedList<Integer>();
		int[] dis = new int[n + 1]; //shortest distance from the starting node
		int[] pre = new int[n + 1]; //keep track of the node previously visited
		boolean[] vis = new boolean[n + 1]; //keep track if visited
		
		q.add(start); //push the starting node into the queue
		vis[start] = true; //mark the starting node visited
		dis[start] = 0; //distance from starting node is 0
		pre[start] = -1; //no previously visited since it's the starting node
		
		while (!q.isEmpty()) {
			int cur = q.poll(); //get the head of the queue
			for (int nxt : adj[cur]) { //get the places the previous node leads to
				if (!vis[nxt]) { //if not visited
					q.add(nxt); //add the newly discovered node to the queue
					vis[nxt] = true; //mark the node visited
					pre[nxt] = cur; //mark down the previously visited node of the current node
					dis[nxt] = dis[cur] + 1; //distance from the starting house, which is one more step than the previous node
					
				}
			}
		}
		
		if (vis[end]) { //if the destination house is marked "true", then it can be reached
			System.out.println("Destination can be reached with " + dis[end] + " steps");
			for (int u = end; u != -1; u = pre[u]) { //print out the shortest path by tracing back to the node it became from
				System.out.print(u + " <- ");
			}
		}else {
			System.out.println("Destination node cannot be reached");
		}	
	}
}
