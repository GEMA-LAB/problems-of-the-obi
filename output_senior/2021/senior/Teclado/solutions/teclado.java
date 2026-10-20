// OBI2021 - Fase 3
// Teclado

import java.util.Scanner;
import java.util.HashMap;
import java.util.Map;

public class teclado {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	Map<Character, String> repr = new HashMap<Character, String>() {{
		put('2', "abc");
		put('3', "def");
		put('4', "ghi");
		put('5', "jkl");
		put('6', "mno");
		put('7', "pqrs");
		put('8', "tuv");
		put('9', "wxyz");
	    }};
	

	String num;
	int m;
  
	num = in.next();
	m = in.nextInt();

	int resp = 0;
	for (int i=0; i<m; i++) {
	    String palavra;
	    palavra = in.next();

	    // se têm comprimentos diferentes não é representação correta
	    if (palavra.length() != num.length())
		continue;
	    Boolean ok = true;
	    // para cada letra da palavra, verifica se é representação correta
	    for (int k=0; k<num.length(); k++) {
		if (repr.get(num.charAt(k)).indexOf(palavra.charAt(k)) == -1) {
		    ok = false;
		    break;
		}
	    }
	    if (ok)
		resp++;
	}
	
	// imprime resposta
	System.out.println(resp);
    }
}
