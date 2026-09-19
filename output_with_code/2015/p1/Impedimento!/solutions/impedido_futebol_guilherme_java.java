/* Guilherme A. Pinto - OBI 2015 - Futebol */

import java.util.Scanner;
import java.io.*;

public class futebol_guilherme_java {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int L, R, D;
	char res;

	L = in.nextInt();
	R = in.nextInt();
	D = in.nextInt();

	res = 'N';
	if ( R > 50 && L < R && R > D ) res = 'S';

	System.out.print(String.format("%c\n", res));
    }

}
