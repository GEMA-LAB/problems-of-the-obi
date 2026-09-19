// OBI2021 - Fase 3
// Sr. Sapo

import java.util.*;
import java.util.Scanner;

public class sapo {
    public static class Pair {
	int x, y;

	Pair(int x, int y) {
	    this.x = x;
	    this.y = y;
	}
    }
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	
	int C = in.nextInt();
	int L = in.nextInt();

	boolean lago[][] = new boolean[C+1][L+1];
	boolean visitado[][] = new boolean[C+1][L+1];

	for (int j=0; j<=L; j++) {
	    for (int i=0; i<=C; i++) {
		lago[i][j] = false;
		visitado[i][j] = false;
	    }
	}

	int P = in.nextInt();
	for (int i = 0; i < P; i++) {
	    int col = in.nextInt();
	    int lin = in.nextInt();
	    lago[col][lin] = true;
	}
	int c_ini = in.nextInt();
	int l_ini = in.nextInt();
	int c_dest = in.nextInt();
	int l_dest = in.nextInt();

	// BFS
	Queue<Pair> q = new LinkedList<Pair>();
	q.add(new Pair(c_ini,l_ini));
	
	// q.push( [c_ini,l_ini] );
	
	String resp = "N";
	while ( q.size() > 0 ) {
	    Pair l = q.remove();
	    int i = l.x;
	    int j = l.y;
	    
	    if (i == c_dest && j == l_dest) {
		resp = "S";
		break;
	    }
    
	    if (!visitado[i][j]) {
		visitado[i][j] = true;
	
		// possiveis pulos
		int a, b;
		for (int dist = 1; dist <= 3; dist++) {
		    a = i + dist; b = j;
		    if ( a <= C && lago[a][b] && !visitado[a][b] )
			q.add( new Pair(a,b) );
		    a = i - dist; b = j;
		    if ( a > 0 && lago[a][b] && !visitado[a][b] )
			q.add( new Pair(a,b) );
		    a = i; b = j + dist;
		    if ( b <= L && lago[a][b] && !visitado[a][b] )
			q.add( new Pair(a,b) );
		    a = i; b = j - dist;
		    if ( b > 0 && lago[a][b] && !visitado[a][b] )
			q.add( new Pair(a,b) );
		}
	    }
	}
	System.out.printf("%s\n", resp);
    }
}
