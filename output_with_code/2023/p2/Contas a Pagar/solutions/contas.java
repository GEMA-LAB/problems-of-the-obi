// OBI2023
// Tarefa Contas a pagar
// r. anido

import java.util.Scanner;
import java.util.Arrays;

public class contas {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int valor = in.nextInt();
		int acougue = in.nextInt();
		int farmacia = in.nextInt();
		int padaria = in.nextInt();

		int resp = 0;
		
		int [] contas = {acougue, farmacia, padaria};
		Arrays.sort(contas);

		if (contas[0] + contas[1] + contas[2] <= valor)
		    resp = 3;
		else if (contas[0] + contas[1] <= valor)
		    resp = 2;
		else if (contas[0] <= valor) 
		    resp = 1;
		else 
		    resp = 0;

		System.out.printf("%d\n", resp);

	}
}
