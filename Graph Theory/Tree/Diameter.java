import java.util.*;
import java.io.*;
/*
find the diameter of a tree, which is the maximum length of a path between two nodes of the tree
from any node (x), find the node that is the furtherst from x
from that node, the longest distance from that node is the diameter of the tree

for each node, solve() calculates the distance of that node from the root node
*the second solve() can be replaced by a function that calculates the height of the tree, with maxHeightNode calculated from the first solve() being the root
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

  public static void solve(int u, int p){ //u is the root node, p is the previous node
    height[u] = height[p] + 1; //find the distance of u from the starting node
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
    height = new int[n + 1]; maxHeight = 0; height[0] = -1; //reset everything
    solve(maxHeightNode, 0); //find the height of the tree with maxHeightNode being the root
    System.out.println(maxHeight); //print out the max height (which is the longest distance -> diameter)
  }
}
