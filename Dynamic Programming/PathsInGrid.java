package DynamicProgramming;

import java.util.Scanner;

/*
Our next problem is to find a path from the upper-left corner to the lower-right
corner of an n ¡Á n grid, such that we only move down and right. Each square
contains a positive integer, and the path should be constructed so that the sum of
the values along the path is as large as possible
sum(y, x) = max(sum(y, x-1),sum(y-1, x))+value[y][x]
 */
public class PathsInGrid {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[][] values = new int[n][n]; //store the input numbers
		for (int i = 0; i < values.length; i++) {
			for (int j = 0; j < values[i].length; j++) {
				values[i][j] = in.nextInt();
			}
		}
		int[][] sum = new int[n][n];
		sum[0][0] = values[0][0];
		sum[1][0] = values[1][0];
		sum[0][1] = values[0][1];
		for (int y = 1; y < values.length; y++) {
			for (int x = 1; x < values[y].length; x++) {
				sum[y][x] = Math.max(sum[y][x-1], sum[y-1][x]) + values[y][x];
			}
		}
		System.out.println(sum[n - 1][n - 1]);
	}

}
