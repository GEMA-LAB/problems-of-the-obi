// R. Anido
// Média e mediana - OBI2021

import java.util.Scanner;

public class media {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int a = in.nextInt();
	int b = in.nextInt();

	// calcula e escreve a resposta
	if (a < b)
	    System.out.println(2*a-b);
	else
	    System.out.println(2*b-a);
    }
}
