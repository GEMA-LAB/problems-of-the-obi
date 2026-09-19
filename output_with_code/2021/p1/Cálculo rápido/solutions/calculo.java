// OBI2021 - Fase 2
// Cálculo rápido

import java.util.Scanner;

public class calculo {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int s, a, b;
    int resposta = 0;

    s = in.nextInt();
    a = in.nextInt();
    b = in.nextInt();

    // para cada número no intervalo, soma os dígitos
    // e compara com s
    for (int i=a; i<=b; i++) {
	int soma = 0, num = i;
	while (num > 0) {
	    soma += num % 10;
	    num = num / 10;
	}
	if (soma == s)
	    resposta++;
    }
    System.out.println(resposta);
  }
}
