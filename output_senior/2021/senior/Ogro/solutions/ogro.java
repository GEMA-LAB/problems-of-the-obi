// OBI2021 - Fase 3
// Ogro

import java.util.Scanner;

public class ogro {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int n = in.nextInt();
  
	// mão esquerda
	if (n >= 5)
	    for (int i=0; i<5; i++)
		System.out.printf("I");
	else if (n > 0)
	    for (int i=0; i<n; i++)
		System.out.printf("I");
	else
	    System.out.printf("*");
	System.out.printf("\n");
  
	n -= 5;
	
	// mão direita
	if (n > 0)
	    for (int i=0; i<n; i++)
		System.out.printf("I");
	else
	    System.out.printf("*");
	System.out.printf("\n");
    }
}
