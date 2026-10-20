// OBI2020
// garamana

import java.util.Scanner;

public class solucao {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	String palavra1 = in.next();
	String palavra2 = in.next();
	int conta1[] = new int[25];
	int conta2[] = new int[25];	

	for (int i = 0; i < palavra1.length(); i++){
	    conta1[palavra1.charAt(i)-'a']++;
	    if (palavra2.charAt(i) != '*')
		conta2[palavra2.charAt(i)-'a']++;
	}
	char resultado = 'S';
	for (int i=0; i<25; i++) {
	    if (conta2[i] >  conta1[i]) {
		resultado = 'N';
		break;
	    }
	}
	System.out.println(resultado);
    }
}
