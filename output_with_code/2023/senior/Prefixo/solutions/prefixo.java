// OBI2023
// Tarefa Prefixo
// r. anido

import java.util.Scanner;

public class prefixo {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		String s1 = in.next();
		int m = in.nextInt();
		String s2 = in.next();

		int resp = 0;
		int i = 0;

		while (i < n && i < m) {
		    if (s1.charAt(i) == s2.charAt(i))
			resp++;
		    else
			break;
		    i++;
		}
		
		System.out.println(resp);

	}
}

