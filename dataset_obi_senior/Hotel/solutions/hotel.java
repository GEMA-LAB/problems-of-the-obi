// OBI2022
// Tarefa Hotel

import java.util.Scanner;

public class hotel {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int d = in.nextInt();
		int a = in.nextInt();
		int n = in.nextInt();
		//vamos usar chegada para calcular o valor da diária
		int chegada = n;

		if (chegada > 15)
		    chegada = 15;

		int diaria = d + (chegada-1)*a;
		
		System.out.printf("%d\n",(31 - n + 1)*diaria);
    
	}
}
