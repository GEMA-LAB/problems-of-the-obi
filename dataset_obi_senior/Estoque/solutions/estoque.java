// OBI2023
// Tarefa Estoque
// r. anido

import java.util.Scanner;

public class estoque {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		int m = in.nextInt();
		
		int[][] estoque = new int[n][m];
		
		for (int i=0; i<n; i++) {
		    for (int j=0; j<m; j++) {
			estoque[i][j] = in.nextInt();
		    }
		}

		int total = 0;
		int p = in.nextInt();

		for (int i=0; i<p; i++) {
		    int tipo = in.nextInt() - 1;
		    int tamanho = in.nextInt() - 1;
		    if (estoque[tipo][tamanho] > 0) {
			estoque[tipo][tamanho] -= 1;
			total += 1;
		    }
		}
		
		System.out.printf("%d\n", total);

	}
}

