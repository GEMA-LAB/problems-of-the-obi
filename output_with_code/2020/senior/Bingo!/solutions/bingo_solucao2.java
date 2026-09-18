// OBI-2020, bingo

import java.util.*;
import java.io.*;
import java.lang.*;

public class solucao2 {

 // public static ArrayList<ArrayList<Integer>> cartelas;
 // public static ArrayList<Integer> cnt;
 // public static ArrayList<Integer> vencedores;

  public static int[][] cartelas;
  public static int[] i_c;

  public static int[] cnt;

  public static int[] vencedores;
  public static int i_v;

  public static int N,K,U;

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
  
    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    N = Integer.parseInt(tokenizer.nextToken());
    K = Integer.parseInt(tokenizer.nextToken());
    U = Integer.parseInt(tokenizer.nextToken());

    // cnt = new ArrayList<Integer>();
    cnt = new int[N+1];
    for( int i = 0; i <= N; i++ ) cnt[i] = 0;

    // cartelas = new ArrayList<ArrayList<Integer>>();
    cartelas = new int[U+1][N+1];
    i_c = new int[U+1];
    for( int i = 0; i <= U; i++ ) i_c[i] = 0;

    for ( int c = 1; c <= N; c++ ){
      line = in.readLine();
      tokenizer = new StringTokenizer(line," ");
      for ( int j = 1; j <= K; j++ ){
        int n = Integer.parseInt(tokenizer.nextToken());
        // cartelas.get(n).add( c );
        cartelas[n][i_c[n]] = c;
        i_c[n]++;
      }
    }

    // vencedores = new ArrayList<Integer>();

    vencedores = new int[N];
    i_v = 0;

    line = in.readLine();
    tokenizer = new StringTokenizer(line," ");

    for ( int i = 1; i <= U && i_v == 0; i++ ){
      int n = Integer.parseInt(tokenizer.nextToken());

      for ( int k = 0; k < i_c[n]; k++ ){
        int c = cartelas[n][k];
        cnt[c]++;
        if ( cnt[c] == K ) {
          vencedores[i_v] = c;
          i_v++;
        }
      }

    }

    String s = "";
    for ( int k = 0; k < i_v; k++ ){
      writer.print( s ); writer.print( vencedores[k] );
      s = " ";      
    }
    writer.println();

    writer.close();
  }
}
