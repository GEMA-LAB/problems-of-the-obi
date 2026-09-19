// OBI2023
// Tarefa Toupeira
// r. anido

import java.util.Scanner;

public class toupeira {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int s = in.nextInt();
		int t = in.nextInt();
		
		boolean[][] adj = new boolean[s][s];
		
		for (int i=0; i<s; i++) {
		    for (int j=0; j<s; j++) {
			adj[i][j] = false;
		    }
		}

		for (int i=0; i<t; i++) {
		    int x = in.nextInt() - 1;
		    int y = in.nextInt() - 1;
		    adj[x][y] = true;
		    adj[y][x] = true;
		}
		
		int p = in.nextInt();

		int total = 0;
		for (int i=0; i<p; i++) {
		    int n = in.nextInt();
		    int corrente = in.nextInt() - 1;
		    boolean ok = true;
		    for (int j=0; j<n-1; j++) {
			int k = in.nextInt() - 1;
			if (adj[corrente][k])
			    corrente = k;
			else {
			    ok = false;
			}
		    }
		    if (ok)
			total += 1;
		}
		System.out.printf("%d\n", total);
	}
}

