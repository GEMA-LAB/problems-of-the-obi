// Guilherme A. Pinto, OBI-2017, carrinho

import java.util.*;
import java.io.*;
import java.lang.*;

public class carrinho_java {

    public static double d[];
    public static double c[];
    public static double dp[][];

    public static double s( int k, int i ){
	// base
	if ( k == 0 ) return 0.0;
	if ( i == -1 ) return Double.MAX_VALUE;
	// memoization
	if ( dp[k][i] != -1.0 ) return dp[k][i];
	
	return dp[k][i] = Math.min(s(k,i-1),s(i,i-1)+(d[k]-d[i])*(d[k]-d[i])/c[i]);
    }
    
    public static void main(String[] args) throws IOException {
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

        int N,i,j;
	
        String line = in.readLine();    
        StringTokenizer tokenizer = new StringTokenizer(line," ");
        N = Integer.parseInt(tokenizer.nextToken());
	
        d = new double[N+1];
        c = new double[N+1];

	d[N] = Double.parseDouble(tokenizer.nextToken());

	for ( i = 0; i < N; i++ ){
	    line = in.readLine();    
	    tokenizer = new StringTokenizer(line," ");
	    d[i] = Double.parseDouble(tokenizer.nextToken());
	    c[i] = Double.parseDouble(tokenizer.nextToken());
	}

	dp = new double[N+1][N+1];
	for ( i = 0; i <= N; i++ )
	    for ( j = 0; j <= N; j++ )
		dp[i][j] = -1.0;

	System.out.format("%.3f%n", s(N,N-1));
    }
}
