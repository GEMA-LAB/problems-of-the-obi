// OBI2022
// Tarefa tanque

import java.util.Scanner;

public class tanque {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int c = in.nextInt();
		int d = in.nextInt();
		int t = in.nextInt();

		double litros = (1.0*d) / (1.0*c);

		double compra = litros - t;
		
		if (compra < 0)
		    compra = 0;
		
		System.out.printf("%.1f\n", compra);
	}
}
