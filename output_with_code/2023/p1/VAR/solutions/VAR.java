// OBI2023
// Tarefa VAR
// r. anido

import java.util.Scanner;
import java.util.Arrays;

public class VAR {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int x = in.nextInt();
		int y = in.nextInt();

		if (x < -8 || x > 8 || y < 0 || y > 8)
		    System.out.println("N");
		else 
		    System.out.println("S");

	}
}
