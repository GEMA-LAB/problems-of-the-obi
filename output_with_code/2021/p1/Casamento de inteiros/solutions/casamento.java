// OBI2021 - Fase 2
// Casamento

import java.util.Scanner;
import java.util.Arrays;
import java.util.LinkedList;

public class casamento {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int resp = 0;
	String a, b;
	
	a = in.next();
	b = in.next();
	// ajusta os tamanhos adicionando zeros à esquerda
	while (a.length() < b.length())
	    a = "0" + a;
	while (b.length() < a.length())
	    b = "0" + b;

	LinkedList<Character> na = new LinkedList<Character>();
	LinkedList<Character> nb = new LinkedList<Character>();

	for (int i=0; i<a.length(); i++) {
	    if (a.charAt(i) == b.charAt(i)) {
		na.add(a.charAt(i));
		nb.add(a.charAt(i));
	    }
	    else if (a.charAt(i) < b.charAt(i))
		nb.add(b.charAt(i));
	    else
		na.add(a.charAt(i));
	}

	int res_a = -1, res_b = -1;
	int multipl;

	
	// calcula valor restante de a
	if (na.size() > 0) {
	    res_a = 0;
	    multipl = 1;
	    for (int i=na.size()-1; i >=0; i--) {
	    res_a += Character.getNumericValue(na.get(i)) * multipl;
	    multipl *= 10;
	    }
	}

	// calcula valor restante de b
	if (nb.size() > 0) {
	    res_b = 0;
	    multipl = 1;
	    for (int i=nb.size()-1; i >=0; i--) {
		res_b += Character.getNumericValue(nb.get(i)) * multipl;
		multipl *= 10;
	    }
	}
	  
	if (res_a > res_b)
	    System.out.printf("%d %d\n",res_b, res_a);
	else
	    System.out.printf("%d %d\n",res_a, res_b);
    }
}
