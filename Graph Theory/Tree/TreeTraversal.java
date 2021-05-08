import java.util.*;
import java.io.*;
/*
traverse through a tree, using dfs
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
  
  static ArrayList<Integer>[] adj; //<node, all of its children nodes>

  public static void dfs(int u, int p){ //u is the current node, p is the previous node
    System.out.println(p + " -> " + u); //process the node
    for (int v : adj[u]){ //for every node u leads to
      if (v != p){ //make sure we don't go in loops, only visit nodes we haven't visited
        dfs(v, u);
      }
    }
  }

  public static void main(String[] args) throws IOException{
    int n = readInt(); //n nodes
    adj = new ArrayList[n + 1];
    for (int i = 0; i < adj.length; i++) adj[i] = new ArrayList<>();
    for (int i = 2; i < adj.length; i++){
      int parent = readInt(); //read in the parent of node i
      adj[parent].add(i); //add that child node to adj[parent]
      adj[i].add(parent); //do the reverse since the child-parent relationship can change depending on how we arrange the root
    }
    
    dfs(1, 0); //dfs(x, 0) means appointing x as the root and start traversing from there
  }

}
