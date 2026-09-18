// OBI2022
// Tarefa caravana
// r. anido

import java.util.Scanner;

public class caravana {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int n = in.nextInt();
	int[] pesos = new int[n];
	int soma = 0;

	for (int i=0; i<n; i++) {
	    int p = in.nextInt();
	    soma += p;
	    pesos[i] = p;
	}
	
	int ideal = soma / n;
	for (int i=0; i<n; i++) {
	    System.out.printf("%d\n", ideal - pesos[i]);
	}
    }  
}
