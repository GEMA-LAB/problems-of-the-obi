// OBI2023
// Tarefa Leilão
// r. anido

import java.util.Scanner;

public class leilao {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		int melhor_valor = 0;
		String melhor_nome = "";
		
		for (int i=0; i<n; i++) {
		    String nome = in.next();
		    int valor = in.nextInt();
		    if (valor > melhor_valor) {
			melhor_valor = valor;
			melhor_nome = nome;
		    }
		}

		System.out.println(melhor_nome);
		System.out.println(melhor_valor);

	}
}

