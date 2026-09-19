// OBI-2019, onibus

import java.util.*;
import java.io.*;
import java.lang.*;

public class onibus_java {

  public static ArrayList<ArrayList<Integer>> g;
  public static int[] d;
  public static int T,L,O,D;

  // BFS
  public static int bfs( int o ){

    Queue<Integer> q = new LinkedList<Integer>();

    d[o] = 0; // visitado, distancia zero
    q.add( o );

    while( !q.isEmpty() ){
      int v = q.remove();
      for ( int u: g.get(v) )
        if ( d[u] == -1 ){ // não visitado
          d[u] = d[v] + 1;
          if ( u == D ) return d[u];
          q.add( u );
        }
    }

    return -1; // não alcançável
  }  

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
  
    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    T = Integer.parseInt(tokenizer.nextToken());
    L = Integer.parseInt(tokenizer.nextToken());
    O = Integer.parseInt(tokenizer.nextToken());
    D = Integer.parseInt(tokenizer.nextToken());

    g = new ArrayList<ArrayList<Integer>>(T+L+1);
    for ( int i = 0; i <= T+L; i++ ) g.add(new ArrayList<Integer>());

    d = new int[T+L+1];
    for ( int i = 0; i <= T+L; i++ ) d[i] = -1;

    for( int i = 1; i <= L; i++ ){
      line = in.readLine();
      tokenizer = new StringTokenizer(line," ");
      int C = Integer.parseInt(tokenizer.nextToken());

      for( int j = 0; j < C; j++ ){
        int t = Integer.parseInt(tokenizer.nextToken());

        g.get(t).add(i+T);
        g.get(i+T).add(t);
      }
    }

    writer.println( bfs(O)/2 );
    writer.close();
  }
}
