/* Guilherme A. Pinto - OBI 2014 - Setas */

import java.util.Scanner;
import java.io.*;

public class guilherme_java {

    static int MAX = 500;
    static char[][] s;
    static int ans;

    public static char solve( int i, int j ){
	int a,b;
	
	if ( s[i][j] == 's' || s[i][j] == '*' )
	    return s[i][j];
	
	a = i; b = j;
	switch( s[i][j] ){
	case 'A': a--; break;
	case 'V': a++; break;
	case '<': b--; break;
	case '>': b++; }
	
	s[i][j] = 's';
	s[i][j] = solve( a, b );
	if ( s[i][j] == '*' ) ans++;
	return s[i][j];
    }
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int i,j,N;

	s = new char[MAX+2][MAX+2];

	N = in.nextInt(); in.nextLine();

	for ( i = 0; i < N+2; i++ ) s[0][i] = '*';

	for ( i = 1; i <= N; i++ ){
	    char[] buf = in.nextLine().toCharArray();
	    s[i][0] = '*';
	    for ( j = 0; j < N; j++ ) 
		s[i][j+1] = buf[j];
	    s[i][N+1] = '*';
	}
	for ( i = 0; i < N+2; i++ ) s[N+1][i] = '*';

	ans = 0;
	for ( i = 1; i <= N; i++ )
	    for ( j = 1; j<= N; j++ )
		if ( s[i][j] != '*' ) 
		    solve ( i, j );

	System.out.print(String.format("%d\n", (N*N)-ans ));
    }

}
