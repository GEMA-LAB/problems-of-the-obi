// OBI2023
// Tarefa Subsequencia
// r. anido

import java.util.Scanner;

public class subsequencia {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int na = in.nextInt();
		int nb = in.nextInt();
		int[] a = new int[na];
		int[] b = new int[nb];
		
		for (int i=0; i<na; i++) {
		    a[i] = in.nextInt();
		}

		for (int i=0; i<nb; i++) {
		    b[i] = in.nextInt();
		}

		char resp = 'S';
		int i = 0, j = 0;

		while (true) {
		    if (a[i] == b[j]) {
			i += 1;
			j += 1;
		    }
		    else {
			i += 1;
		    }

		    if (j == b.length)
			break;
		    if (i == a.length) {
			resp = 'N';
			break;
		    }
		}
		
		System.out.printf("%c\n", resp);

	}
}

