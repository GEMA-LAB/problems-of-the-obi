// Sequência secreta
// OBI2019
// R. Anido

import java.util.Scanner;

public class secreta_java {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int n, x; 
	int atual; // último valor marcado na sequência
	int total; // total de valores marcados

	n = in.nextInt();
	atual = -1;  //inicializa com um número diferente dos valores 1 e 2
	total = 0;  // total de números marcados

	for (int i=0; i<n; i++) {
	    x = in.nextInt();
	    // cada vez que encontra um número diferente do 
	    // último marcado, marca esse novo número
	    if (atual != x) {
		atual = x;
		total += 1;
	    }
	}
	
	System.out.println(total);
    }
}
