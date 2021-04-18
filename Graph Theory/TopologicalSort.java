package Graph;
import java.io.*;
import java.util.*;
//Topological Sorting is ordering of vertices or nodes such if there is an edge between (u,v) 
//then u should come before v in topological sorting
//it's for acyclic, directed graph
/*
- find vertex with no incoming edge
- print vertex, remove vertex and remove edge
- apply this to other vertices
Adjacent list with in-degree
Queue to store vertex with no incoming edge, ready to be processed
PriorityQueue to constantly put least value first
- Poll a vertex from Queue, reduce in-degree for the vertices it leads to 
If that vertex has degree 0, push it to Queue

If you can process with topological sort, it means there's no cycle

void topsort(graph G){
	Queue Q;
	int counter = 0;
	vertex v, w;
	Q = create queue();
	for each vertex v
		if (indegree[v] == 0){
			Q.add(v); //push to queue when it has no incoming edge
		}
	while (!Q.isEmpty()){
		v = Q.poll(); //get a vertex
		counter++; //keep track of the number of vertices processed
		for each w adjacent to v{
			if (--indegree[w] == 0){ 
			//subtract one incoming edge (caused by removing the vertex being processed)
			//see if it now has 0 incoming edge
				queue.add(w);
			}
		}
	}
	if (counter != NUM_VERTEX){ //check if number of vertices processed is same as total vertices
		print ("graph has a cycle"); //if not, graph has a cycle
	}
}
 */
public class TopologicalSort {
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
		int n = readInt(), m = readInt(); //n nodes, m directed edges
		int inDegree[] = new int[n]; //store in degree
		List<Integer>[] adj = new ArrayList[n];
		for (int i = 0; i < n; i++) adj[i] = new ArrayList<Integer>();
		for (int i = 0; i < m; i++) {
			int from = readInt() - 1, to = readInt() - 1;
			adj[from].add(to); inDegree[to]++;
		}
		
		PriorityQueue<Integer> q = new PriorityQueue();
		for (int i = 0; i < n; i++) {
			if (inDegree[i] == 0) q.add(i); //find starting nodes (vertex whose inDegree is 0)
		}
		List<Integer> ans = new ArrayList(); //a list of answers
		while(!q.isEmpty()) {
			int u = q.poll(); //get the first element from the queue, to be processed
			ans.add(u); //add the vertex to the answer list
			for (int v : adj[u]) { //for every vertex the current vertex leads to
				inDegree[v]--; //decrease its in degree by 1
				if(inDegree[v] == 0) q.add(v); //if in degree is 0, add it to the queue
			} 
		}
		if (ans.size() != n) { 
			//if number of elements processed != the number of original, meaning some are not processed
			System.out.println("A cycle exists, cannot complete all tasks");
		}else {
			for (int i : ans) {
				System.out.print(i + 1 + " ");
			}
		}
	}
}