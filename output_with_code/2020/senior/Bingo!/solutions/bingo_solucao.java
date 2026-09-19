// OBI-2020, bingo

import java.util.*;
import java.io.*;
import java.lang.*;

public class solucao {

  public static ArrayList<ArrayList<Integer>> cartelas;
  public static ArrayList<Integer> cnt;
  public static ArrayList<Integer> vencedores;

  public static int N,K,U;

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
  
    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    N = Integer.parseInt(tokenizer.nextToken());
    K = Integer.parseInt(tokenizer.nextToken());
    U = Integer.parseInt(tokenizer.nextToken());

    cnt = new ArrayList<Integer>();
    for( int i = 0; i <= N; i++ ) cnt.add(0);

    cartelas = new ArrayList<ArrayList<Integer>>();
    for( int i = 0; i <= U; i++ ) cartelas.add( new ArrayList<Integer>() );

    for ( int c = 1; c <= N; c++ ){
      line = in.readLine();
      tokenizer = new StringTokenizer(line," ");
      for ( int j = 1; j <= K; j++ ){
        int n = Integer.parseInt(tokenizer.nextToken());
        cartelas.get(n).add( c );
      }
    }

    vencedores = new ArrayList<Integer>();

    line = in.readLine();
    tokenizer = new StringTokenizer(line," ");

    for ( int i = 1; i <= U && vencedores.size() == 0; i++ ){
      int n = Integer.parseInt(tokenizer.nextToken());

      for ( int c: cartelas.get(n) ){
        cnt.set( c, cnt.get(c)+1 );
        if ( cnt.get(c) == K ) vencedores.add( c );
      }
    }

    String s = "";
    for ( int c : vencedores ){
      writer.print( s ); writer.print( c );
      s = " ";
    }
    writer.println();

    writer.close();
  }
}
