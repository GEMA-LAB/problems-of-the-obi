// OBI2021 - Fase 2
// Potência

import java.util.Scanner;

public class potencia {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int n, t;
    long resposta = 0;
    int potencia, p, base;
  
    n = in.nextInt();

    for (int i=0; i<n; i++) {
	t = in.nextInt();
	// separa o último dígito do termo
	p = t % 10;
	base = t / 10;

	// calcula o valor do termo
	potencia = 1;
	for (int j=0; j<p; j++)
	    potencia *= base;

	// acumula no valor total
	resposta += potencia;
    }
    System.out.println(resposta);
  }
}
