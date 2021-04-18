package Graph;

import java.util.*;
import java.io.*;

//https://codeforces.com/problemset/problem/59/E
public class PracticeForbiddenEdges {
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
	
	public static void main(String[] args) throws IOException{
		int n = readInt(), m = readInt(), k = readInt(); //n nodes, m edges, k forbidden roads
		//create an array that contains ArrayList of Integer
		List<Integer>[] adj = new ArrayList[n + 1]; //adjacency list
		for (int i = 0; i < adj.length; i++) {
			adj[i] = new ArrayList<>();
		}
		int start = 1, end = n; 
		boolean[][] g = new boolean[n + 1][n + 1];
		for (int i = 1; i <= m; i++) {
			int u = readInt(), v = readInt();
			adj[u].add(v);
			adj[v].add(u);
			g[u][v] = true; g[v][u] = true;
		}
		
		final int MAX = 3000;
		HashSet<Long> set = new HashSet<>();
		for (int i = 0; i < k; i++) {
			set.add((long) MAX * MAX * readInt() + MAX * readInt() + readInt());
		}
		
		Queue<Integer> q = new LinkedList<>();
		int[][] dis = new int[n + 1][n + 1]; 
		int[][] pre = new int[n + 1][n + 1]; //keep track of the node previously visited
		int secondLast = -1;
		
		q.add(1 * MAX); 
		dis[start][start] = 1; 
		
		while (!q.isEmpty()) {
			int cur = q.poll(); //get the head of the queue
			int a = cur % MAX; //previous node
        	int b = cur / MAX; //current node
        	if(b == end){ //if current node is our destination node, we break
        		secondLast = a; //keep track of the node leading to the destination node
        		break;
        	}
			for (int nxt = 1; nxt <= n; nxt++) {
				if(dis[b][nxt] != 0) continue;
				if (!g[b][nxt]) continue; //if there is no route leading from b to nxt, continue loop
				if (!set.contains((long) MAX * MAX * a + MAX * b + nxt)) {
					q.add(MAX * nxt + b); 
					pre[nxt][b] = a; 
					dis[b][nxt] = dis[a][b] + 1;
				}
			}
		}
		
		if (secondLast != -1) {
			ArrayList<Integer> path = new ArrayList<>();
			int distance = 1;
	        int i = end;
	        path.add(secondLast); path.add(end);
	        int from = secondLast;
        	while(true){
        		int a = pre[i][from];
        		if(a == 0) break;
        		path.add(0, a);
        		distance++;
        		i = from;
        		from = a;
        	}
        	System.out.println(distance);
        	for(int j = 0; j < path.size(); j++) System.out.print(path.get(j) + " ");
			
		}else {
			System.out.println(-1);
		}
		
	}
}
