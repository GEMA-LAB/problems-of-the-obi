// OBI2023
// Tarefa Chinelos
// r. anido

import java.util.Scanner;

public class chinelos {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		int[] estoque = new int[n];
		
		for (int i=0; i<n; i++) {
		    estoque[i] = in.nextInt();
		}

		int total = 0;
		int p = in.nextInt();

		for (int i=0; i<p; i++) {
		    int pedido = in.nextInt() - 1;
		    if (estoque[pedido] > 0) {
			estoque[pedido] -= 1;
			total += 1;
		    }
		}
		
		System.out.printf("%d\n", total);

	}
}

