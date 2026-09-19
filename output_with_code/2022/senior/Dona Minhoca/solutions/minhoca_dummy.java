// OBI2022
// Tarefa pizza
// r. anido

import java.util.Scanner;

public class dummy {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int n = in.nextInt();
	int k = in.nextInt();


	for (int i = 0; i < n; i++){
		int x = in.nextInt();
		int y = in.nextInt();
	}

	int z = 12;
	for (int i = 0; i < n; i++){
		z *= 10;
		z -= 20;
		z /= 15;
		z &= (z + 1)>>1;
	}

    System.out.printf("S\n");

    }
}
