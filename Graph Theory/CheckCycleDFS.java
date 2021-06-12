import java.util.*;

public class DFSTemplate {
  static int[] dis, prev;
  static boolean[] vis;
  static ArrayList<Integer>[] adj;
  static boolean cycle;
  public static void main(String[] args){
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), m = in.nextInt();
    adj = new ArrayList[n];
    for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();
    for (int i = 0; i < m; i++){
      int a = in.nextInt(), b = in.nextInt();
      adj[a].add(b); adj[b].add(a);
    }
    dis = new int[n]; prev = new int[n]; prev[0] = -1; vis = new boolean[n];
    dfs(0);
    System.out.println(cycle);
    System.out.println(dis[n - 1]);
  }
  public static void dfs(int node){
    for (int nxt : adj[node]){
      if (!vis[nxt]){
        vis[nxt] = true;
        dis[nxt] = dis[node] + 1;
        prev[nxt] = node;
      }else if (prev[node] != nxt){ 
      //if the next node has already been visited and it's not the node where the current node came from, a back edge exists and there is a cycle
        cycle = true;
      }
    }
  }
}
