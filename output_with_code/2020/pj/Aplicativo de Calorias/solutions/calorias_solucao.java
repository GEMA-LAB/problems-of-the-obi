// OBI2020 - Fase 3
// calorias

import java.util.Scanner;

public class solucao {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int larg, compr;
	int e1 = in.nextInt();
	int e2 = in.nextInt();
	int e3 = in.nextInt();
	int x = in.nextInt();

	if (e2 - e1 <= x)
	    System.out.println(e2);
	else
	    System.out.println(e3);
    }
}
