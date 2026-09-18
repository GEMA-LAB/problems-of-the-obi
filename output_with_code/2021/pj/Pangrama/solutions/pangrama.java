// R. Anido
// Pangrama - OBI2021

import java.util.Scanner;
import java.util.Set;
import java.util.HashSet;


public class pangrama {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	String linha = in.nextLine();
	Set<Character> s = new HashSet();
	for (int i = 0; i < linha.length(); i++)
	    s.add(linha.charAt(i));
	s.remove( ' ' );
	s.remove( ':' );
	s.remove( ',' );
	if (s.size() == 23)
	    System.out.println('S');
	else
	    System.out.println('N');
    }
}
