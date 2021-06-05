//given four coordinates, calculate the total value covered inside the rectangle
public class Main{
  static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	static StringTokenizer st;
	static String next () throws IOException {
		while (st == null || !st.hasMoreTokens())
			st = new StringTokenizer(br.readLine().trim());
		return st.nextToken();
	}
	static int readInt () throws IOException {
		return Integer.parseInt(next());
	}
  
  public static void main(String[] args) throws IOException{
    int row = readInt(), col = readInt(); //number of rows and columns of the 2d array
    int[][] psa = new int[row + 1][col + 1];
    for (int i = 1; i <= row; i++){
      for (int j = 1; j <= col; j++){
        int num = readInt();
        psa[i][j] = num + psa[i - 1][j] + psa[i][j - 1] - psa[i - 1][j - 1];
      }
    }
    //topleft and bottomright coordinates of the rectangle
    int r1 = readInt(), c1 = readInt(), r3 = readInt(), c3 = readInt();
    int ans = psa[r3][c3] - psa[r3][c1 - 1] - psa[r1 - 1][c3] + psa[r1 - 1][c1 - 1];
    System.out.println(ans);
  }
}
