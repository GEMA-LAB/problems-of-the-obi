/* Guilherme A. Pinto - OBI 2014 - Triangulo */

import java.util.Scanner;
import java.io.*;

public class guilherme_java {

    public static boolean triangulo( int p, int q, int r  ){
	if ( p < q+r && q < p+r && r < p+q ) return true;
	return false;
    }

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int a,b,c,d;

	a = in.nextInt();
	b = in.nextInt();
	c = in.nextInt();
	d = in.nextInt();

	if ( triangulo( a, b, c ) ||
	     triangulo( a, b, d ) ||
	     triangulo( a, c, d ) ||
	     triangulo( b, c, d ) ) System.out.print("S\n");
	else  System.out.print("N\n");
    }
}
