// OBI2022
// Tarefa jogo
// r. anido

import java.util.Scanner;

public class jogo {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int x = in.nextInt();

	while (true) {
	    int t = in.nextInt();
	    if (t > x)
		System.out.printf("menor\n");
	    else if (t < x)
		System.out.printf("maior\n");
	    else {
		System.out.printf("correto\n");
		break;
	    }
	}
    }
}
