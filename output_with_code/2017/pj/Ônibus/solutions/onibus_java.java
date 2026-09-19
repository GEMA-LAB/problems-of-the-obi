// Guilherme A. Pinto, OBI-2017, onibus

import java.util.*;
import java.io.*;
import java.lang.*;

public class onibus_java {
    
    public static int N,A,B;
    public static ArrayList<ArrayList<Integer>> g;
    
    public static boolean dfs( int atual, int pai, int dist, int destino ){

	if ( atual == destino ){
	    System.out.println( dist );
	    return true;
	}
  
	for ( int p: g.get(atual) )
	    if ( p != pai )
		if ( dfs( p, atual, dist + 1, destino ) )
		    return true;
	
	return false;
    }    
    
    public static void main(String[] args) throws IOException {
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        String line = in.readLine();    
        StringTokenizer tokenizer = new StringTokenizer(line," ");
        N = Integer.parseInt(tokenizer.nextToken());
        A = Integer.parseInt(tokenizer.nextToken());
        B = Integer.parseInt(tokenizer.nextToken());
	
	g = new ArrayList<ArrayList<Integer>>(N+1);

	for ( int i = 0; i <= N; i++ )
	    g.add(new ArrayList<Integer>());
	
	for ( int i = 1; i <= N-1; i++ ){
	    line = in.readLine();
	    tokenizer = new StringTokenizer(line," ");
	    int P = Integer.parseInt(tokenizer.nextToken());
	    int Q = Integer.parseInt(tokenizer.nextToken());
	    g.get(P).add(Q);
	    g.get(Q).add(P);
	}

	dfs( A, -1, 0, B );
    }
}
