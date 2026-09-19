// R. Anido
// Nota - OBI2019

import java.util.Scanner;
import java.lang.Math;

public class nota {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int b = in.nextInt();
	int t = in.nextInt();

	int felix = Math.min(b,t);      // base Felix
	int marzia = 160-Math.max(b,t); // base Marzia
	
	if (felix > marzia)
	    System.out.println(1);
	else if (felix < marzia)
	    System.out.println(2);
	else
	    System.out.println(0);
    }
}
