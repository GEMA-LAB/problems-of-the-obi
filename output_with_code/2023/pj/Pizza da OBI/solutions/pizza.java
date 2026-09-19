// OBI2023
// Tarefa Pizza
// r. anido

import java.util.Scanner;

public class pizza {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		int g = in.nextInt();
		int m = in.nextInt();

		int sobra =  g*8 + m*6 - n;

		if (sobra < 0)
		    sobra = 0;
		
		System.out.println(sobra);

	}
}

