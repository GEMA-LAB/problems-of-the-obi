// OBI2023
// Tarefa Prêmio
// r. anido

import java.util.Scanner;
import java.util.Arrays;

public class premio {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int pao = in.nextInt();
		int doce = in.nextInt();
		int bolo = in.nextInt();

		int pontos = pao + 2*doce + 3*bolo;
		
		if (pontos >= 150) 
		    System.out.println("B");
		else if (pontos >= 120)
		    System.out.println("D");
		else if (pontos >= 100)
		    System.out.println("P");
		else
		    System.out.println("N");
	}
}
