// OBI2022
// Tarefa teste de redacao

import java.util.Scanner;

public class teste {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		int m = in.nextInt();

		String letras = "abcdefghijklmnopqrstuvwxyz";

		for (int i=1; i<=m; i++) {
		    int x = i;
		    while (x > 0) {
			System.out.printf("%c", letras.charAt(x % 10));
			x /= 10;
			System.out.printf(" ");
		    }
		}
		
		System.out.printf("\n");

	}
}

