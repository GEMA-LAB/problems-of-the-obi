// OBI2022
// Tarefa Maior

import java.util.Scanner;

public class maior {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int N = in.nextInt();
		int M = in.nextInt();
		int S = in.nextInt();
		boolean achou = false;
		int resp = 0; // java quer que inicialize, embora neste caso não precise...
		
		for (int i=M; i>N; i--) {
		    int soma = 0;
		    int x = i;
		    while (x > 0) {
			soma += x % 10;
			x /= 10;
		    }
		    if (soma == S) {
			achou = true;
			resp = i;
			break;
		    }
		}	    

		if (achou)
		    System.out.println(resp);
		else
		    System.out.println(-1);
	}
}
