// OBI2020
// musica

import java.util.Scanner;

public class solucao {
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int n = in.nextInt();
	int m = in.nextInt();
	int tocando = in.nextInt();
	int[] favorita = new int[m];
	int[] visitado = new int[m];
	int trocas = 0;

	for (int i=0; i<m; i++){
	    favorita[i] = -1;
	    visitado[i] = 0;
	}
	
	tocando--;
	for (int i=0; i<n; i++){
	    int a = in.nextInt();
	    int b = in.nextInt();
	    a--; b--;
	    if (favorita[b] == -1)
		favorita[b] = a;
	}
	
	while(visitado[tocando] == 0 && favorita[tocando] != -1){
	    trocas++;
	    visitado[tocando] = 1;
	    tocando = favorita[tocando];
	}
	
	if (visitado[tocando] == 0)
	    System.out.println(trocas);
	else
	    System.out.println(-1);
    }
}
