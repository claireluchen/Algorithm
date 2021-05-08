import java.util.*;
import java.io.*;
/*
find the height of each node in a tree
(the height of the bottom node is 0)
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
  static int[] height; //height[i] = height of subtree of node i
  
  public static void solve(int u, int p){
  //  height[u] = 1; use this line if you want the height of the bottom node to be 1
    for (int v : adj[u]){ //for every node u leads to
      if (v != p){ //make sure we don't go in loops
        solve(v, u);
        height[u] = Math.max(height[v] + 1, height[u]);
      }
    }
  }

  public static void main(String[] args) throws IOException{
    n = readInt(); //n nodes
    adj = new ArrayList[n + 1];
    for (int i = 0; i < adj.length; i++){
      adj[i] = new ArrayList<>();
    }
    height = new int[n + 1];
    //assume 1 is the root node
    //for nodes 2 to n, read in its parent node
    for (int u = 2; u <= n; u++){
      int parent = readInt(); //read in the parent node of u
      adj[parent].add(u);
    }
    
    solve(1, 0);
    for (int i = 1; i < height.length; i++){
      System.out.println(i + " " + height[i]);
    }
  }
}
