import java.util.*;
import java.io.*;
/*
find the diameter of a tree, which is the maximum length of a path between two nodes of the tree
from any node (x), find the node that is the furtherst from x
from that node, the longest distance from that node is the diameter of the tree

solve() finds the distance of each node from the starting node, call the farthest node from the starting node n
solve2() finds the height of the tree with n being the root, the greatest height is the diameter of the tree
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
  static int maxHeight;
  static int maxHeightNode;

  public static void solve(int u, int p){
    height[u] = height[p] + 1; //go through each node (u) and find the distance of u from the starting node
    if (maxHeight < height[u]){ //check if this current node (u) has the max distance from the starting node
      maxHeight = height[u];
      maxHeightNode = u;
    }
    for (int v : adj[u]){
      if (v != p){      
        solve(v, u);
      }
    }
  }

  public static void solve2(int u, int p){ //find height of the tree with u being the root
  //  height[u] = 1; use this line if you want the height of the bottom node to be 1
    for (int v : adj[u]){ 
      if (v != p){ 
        solve(v, u);
        height[u] = Math.max(height[v] + 1, height[u]);
        maxHeight = Math.max(maxHeight, height[u]);
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
      adj[u].add(parent);
    }
    
    height[0] = -1;
    solve(1, 0); //find the fartherst node from a given node (1 in this case)
    height = new int[n + 1]; maxHeight = 0; //reset everything
    solve2(maxHeightNode, 0); //find the height of the tree with maxHeightNode being the root
    System.out.println(maxHeight); //print out the max height (which is the longest distance -> diameter)
  }
}
