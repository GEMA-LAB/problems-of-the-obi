// OBI2022
// Tarefa Magico

import java.util.Scanner;

public class magico {

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int n = in.nextInt();
	int ii=-1, jj=-1;
	
	int[][] magico = new int[n][n];
	
	for (int i=0; i<n; i++) {
	    for (int j=0; j<n; j++ ) {
		magico[i][j] = in.nextInt();
		if (magico[i][j] == 0) {
		    ii = i;
		    jj = j;
		}
	    }
	}
	
	// soma correta
	int soma = 0;
	for (int i=0; i<n; i++) {
	    if (i == ii) continue;
	    for (int j=0; j<n; j++ ) {
		soma += magico[i][j];
	    }
	    break;
	}
	
	// soma sem o número ilegível
	int s = 0;
	for (int j=0; j<n; j++ ) {
	    s += magico[ii][j]; 
	}
	
	// imprime a resposta
	System.out.printf("%d\n", soma - s);
	System.out.printf("%d\n", ii+1);
	System.out.printf("%d\n", jj+1);
    }
}
