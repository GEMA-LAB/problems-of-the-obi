// Guilherme A. Pinto, OBI-2017, visita

import java.util.*;
import java.io.*;
import java.lang.*;

public class visita_java {
    
    public static class Pii
    {
	public int first,second;
	
	public Pii( int f, int s ) {
	    first = f;
	    second = s;
	}
    }
    
    public static int N,A,B;
    public static ArrayList<ArrayList<Pii>> g;
    
    public static boolean dfs( int atual, int pai, int dist, int destino ){

	if ( atual == destino ){
	    System.out.println( dist );
	    return true;
	}
  
	for ( Pii p: g.get(atual) ){
	    int c = p.first;
	    int d = p.second;
	    if ( c != pai )
		if ( dfs( c, atual, dist + d, destino ) )
		    return true;
	}
	
	return false;
    }    
    
    public static void main(String[] args) throws IOException {
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        String line = in.readLine();    
        StringTokenizer tokenizer = new StringTokenizer(line," ");
        N = Integer.parseInt(tokenizer.nextToken());
        A = Integer.parseInt(tokenizer.nextToken());
        B = Integer.parseInt(tokenizer.nextToken());
	
	g = new ArrayList<ArrayList<Pii>>(N+1);

	for ( int i = 0; i <= N; i++ )
	    g.add(new ArrayList<Pii>());
	
	for ( int i = 1; i <= N-1; i++ ){
	    line = in.readLine();
	    tokenizer = new StringTokenizer(line," ");
	    int P = Integer.parseInt(tokenizer.nextToken());
	    int Q = Integer.parseInt(tokenizer.nextToken());
	    int D = Integer.parseInt(tokenizer.nextToken());
	    g.get(P).add(new Pii(Q,D));
	    g.get(Q).add(new Pii(P,D));
	}

	dfs( A, -1, 0, B );
    }
}
