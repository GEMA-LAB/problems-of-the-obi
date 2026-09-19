// OBI-2019, colecao

import java.util.*;
import java.io.*;
import java.lang.*;

public class colecao_java {

  public static ArrayList<ArrayList<Integer>> block;
  public static TreeSet<Integer> ans;

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
  
    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int N = Integer.parseInt(tokenizer.nextToken());
    int M = Integer.parseInt(tokenizer.nextToken());

    block = new ArrayList<ArrayList<Integer>>(N+1);
    for ( int i = 0; i <= N; i++ ) block.add(new ArrayList<Integer>());

    for ( int i = 1; i <= M; i++ ){
      line = in.readLine();
      tokenizer = new StringTokenizer(line," ");
      int u = Integer.parseInt(tokenizer.nextToken());
      int v = Integer.parseInt(tokenizer.nextToken());

      block.get(u).add(v);
      block.get(v).add(u);
    }

    ans = new TreeSet<Integer>();

    for ( int i = N; i >= 1; i-- ){
      boolean can = true;

      for ( int w: block.get(i) ){
        if( ans.contains(w) )
          can = false;
      }

      if ( can ) ans.add( i );
    }

    writer.println( ans.size() );

    int i = 1;

    for( int w: ans ){

      if( i < ans.size() ){
        writer.print( w ); writer.print( " " );
      } else writer.println( w );

      i++;
    }

    writer.close();
  }
}
