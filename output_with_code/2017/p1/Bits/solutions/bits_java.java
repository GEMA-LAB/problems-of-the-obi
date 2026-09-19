// Guilherme A. Pinto, OBI-2017, bits

import java.util.*;
import java.io.*;
import java.lang.*;

public class bits_java {

    public static int MOD = 1000000007;    
    
    public static void main(String[] args) throws IOException {
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	PrintWriter writer = new PrintWriter(System.out);

        int N,K;
	
        String line = in.readLine();    
        StringTokenizer tokenizer = new StringTokenizer(line," ");
        N = Integer.parseInt(tokenizer.nextToken());
        K = Integer.parseInt(tokenizer.nextToken());
	
        int dp[] = new int[N+1];
        int pot2[] = new int[N+1];

	pot2[0] = 1;
	for ( int i = 1; i <= N; i++ )
	    pot2[i] = (pot2[i-1]*2)%MOD;
	
	for ( int i = 1; i <= N; i++ ){
	    if ( i < K ) dp[i] = pot2[i];
	    else if ( i == K ) dp[i] = pot2[i]-1;
	    else {
		dp[i] = 0;
		for ( int k = 1; k <= K; k++ )
		    dp[i] = (dp[i]+dp[i-k])%MOD;
	    }
	}

	writer.println( dp[N] );	
	writer.close();
    }
}
