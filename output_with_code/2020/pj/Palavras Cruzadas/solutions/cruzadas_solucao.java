// OBI2020
// palavras cruzadas

import java.util.Scanner;

public class solucao {
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int indice_h = -1, indice_v = -1;

	char horizontal[] = in.next().toCharArray();
	char vertical[] = in.next().toCharArray();
	boolean ok = true;
	for (int i=horizontal.length-1; i>=0; i--) {
	    for (int j=vertical.length-1; j>=0; j--) {
		if (horizontal[i] == vertical[j]) {
		    indice_h = i+1;
		    indice_v = j+1;
		    ok = false;
		    break;
		}
	    }
	    if (!ok)
		break;
	}
	System.out.println(indice_h+" "+indice_v);
    }
}
