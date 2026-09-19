// OBI2022
// Tarefa pizza
// r. anido

import java.util.Scanner;

public class pizza {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int a = in.nextInt();
	int b = in.nextInt();
	int raio = in.nextInt();
	int grau = in.nextInt();

	boolean ok = true;

	if (2*raio > a || 2*raio > b)
	    ok = false;
	
	if ((360 % grau) != 0)
	    ok = false;
	
	if (ok)
	    System.out.printf("S\n");
	else
	    System.out.printf("N\n");

    }
}
