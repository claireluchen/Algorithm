import java.util.*;
import java.io.*;
/*
find the size of each subtree in a tree
*/
public class Main {
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

  static int n;
  static ArrayList<Integer>[] adj; //<node, all nodes it is connected to>
  static int[] size; //size[i] = size of subtree of node i

  public static void solve(int u, int p){
    size[u] = 1;
    for (int v : adj[u]){ //for every node u leads to
      if (v != p){ //make sure we don't go in loops
        solve(v, u);
        size[u] += size[v];
      }
    }
  }

  public static void main(String[] args) throws IOException{
    n = readInt(); //n nodes, nodes starting from 1 to n
    adj = new ArrayList[n + 1];
    for (int i = 0; i < adj.length; i++){
      adj[i] = new ArrayList<>();
    }
    size = new int[n + 1];
    //assume 1 is the root node
    //for nodes 2 to n, read in its parent node
    for (int u = 2; u <= n; u++){
      int parent = readInt();
      adj[parent].add(u);
    }
    
    solve(1, 0);
    System.out.println(size[1]);
  }
}
