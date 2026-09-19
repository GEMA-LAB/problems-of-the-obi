// OBI2020 - Fase 2
// quebra

import java.util.Scanner;
import java.util.Arrays;

public class solucao {
    public static final int MAX = 200;
    public static int[] distancia = new int[MAX];
    public static boolean[][] adj = new boolean[MAX][MAX];
    public static int alcancados = 0;
    public static int S;
    
    public static int busca(int k) {
	if (distancia[k] == -1) {
	    distancia[k] = 0;
	    for (int q = 0; q < S; q++) {
		if (adj[k][q])
		    distancia[k] = Math.max(1 + busca(q), distancia[k]);
	    }
	}
	return distancia[k];
    }
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	int[] altura = new int[MAX];
	int i, a, b;

	S = in.nextInt();
	int T = in.nextInt();
	int P = in.nextInt();
	for(i=0; i<S; i++) {
	    altura[i] = in.nextInt();
	    distancia[i] = -1;
	}
	for (i=0; i<T; i++) {
	    a = in.nextInt();
	    b = in.nextInt();
	    a--; b--;
	    if (altura[a] > altura[b])
		adj[a][b] = true;
	    else if (altura[a] < altura[b])
		adj[b][a] = true;
	}

	System.out.println(busca(P-1));
    }
}

