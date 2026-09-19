// OBI2021
// Cifras

import java.util.Scanner;

public class cifra {

    public static void main(String[] args) {
	char[] consoante =        "bcdfghjklmnpqrstvxz".toCharArray();
	char[] vogal_mais_prox =  "aaeeeiiiiooooouuuuu".toCharArray();
	char[] prox_consoante =   "cdfghjklmnpqrstvxzz".toCharArray();
	Scanner in = new Scanner(System.in);
	
	char[] s = in.nextLine().toCharArray();

	for (char c : s) {
	    // primeira letra é sempre copiada, vogal ou consoante
	    System.out.print(c);

	    // segunda e terceira letra, apenas se consoante
	    int indice;
	    for (indice=0; indice<consoante.length ; indice++)
		if (consoante[indice] == c)
		    break;
	    if (indice < consoante.length) {
		System.out.print(vogal_mais_prox[indice]);
		System.out.print(prox_consoante[indice]);
	    }
	}
	System.out.println();
    }
}
