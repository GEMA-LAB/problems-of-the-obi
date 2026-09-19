// OBI2021
// Tarefa Idade
// 17293-F
// Heitor Dalaneze Pires

import java.util.Scanner;

public class idade {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int idade1 = in.nextInt();
		int idade2 = in.nextInt();
		int idade3 = in.nextInt();
		
		
		int idade_middle = 0;
		
		if(idade1 >= idade2 && idade1 >= idade3) {
			idade_middle = Math.max(idade2, idade3);
		} else if(idade2 >= idade1 && idade2 >= idade3) {
			idade_middle = Math.max(idade1, idade3);
		} else if(idade3 >= idade1 && idade3 >= idade2) {
			idade_middle = Math.max(idade1, idade2);
		}
		
		System.out.printf("%d\n", idade_middle);
	}
}
