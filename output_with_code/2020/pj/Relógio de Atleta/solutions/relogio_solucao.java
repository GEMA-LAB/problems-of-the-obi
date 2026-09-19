// OBI2020
// relogio

import java.util.Scanner;

public class solucao {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int r = in.nextInt();
	int f = in.nextInt();
	int c = in.nextInt();

	if (f > 3*r || c < 95)
	    System.out.println("diminuir");
	else if (f < 2*r && c > 97)
	    System.out.println("aumentar");
	else
	    System.out.println("manter");
    }
}
