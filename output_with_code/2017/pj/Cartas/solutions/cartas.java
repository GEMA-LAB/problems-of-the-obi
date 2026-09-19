// r. anido
// problema cartas, OBI2017

import java.util.Scanner;

public class cartas {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in); 
	int a = in.nextInt();
	int b = in.nextInt();
	int c = in.nextInt();
	
	if (a==b)
	    System.out.println(c);   // se carta A é igual a carta B, resposta é C
	else if (a==c)
	    System.out.println(b);   // se carta A é igual a carta C, resposta é B
	else
	    System.out.println(a);   // senão a resposta é A (cartas C e B são iguais)
    }
}
