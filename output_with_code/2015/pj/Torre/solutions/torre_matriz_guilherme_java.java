/* Guilherme A. Pinto, OBI 2015, torre */

import java.util.Scanner;
import java.io.*;

public class matriz_guilherme_java {

    static int MAX = 1000;
    static int[][] M;
    static int[] L,C;
    
    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int i,j,k,N,max,p;

	M = new int[MAX][MAX];
	L = new int[MAX];
	C = new int[MAX];
	
	N = in.nextInt();
	for( i = 0; i < N; i++ )
	    for( j = 0; j < N; j++ )
		M[i][j] = in.nextInt();
	
	for( i = 0; i < N; i++ ){
	    L[i] = C[i] = 0;
	    for( k = 0; k < N; k++ ){
		L[i] += M[i][k];
		C[i] += M[k][i];
	    }
	}
	
	max = -1;
	for( i = 0; i < N; i++ )
	    for( j = 0; j < N; j++ ){
		p = L[i]+C[j]-2*M[i][j];
		max = max > p ? max : p;
	    }

	System.out.print(String.format("%d\n", max));
    }

}
