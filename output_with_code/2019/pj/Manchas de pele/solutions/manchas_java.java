// OBI-2019, manchas

import java.util.*;
import java.io.*;
import java.lang.*;

public class manchas_java {

  public static class Pii
  {
      public int first,second;
      
      public Pii( int f, int s ) {
          first = f;
          second = s;
      }
  }

  public static int[] di = {1,0,-1,0};
  public static int[] dj = {0,1,0,-1};

  public static int[][] m;
  public static Queue<Pii> q;
  public static int N,M,cnt;

  // BFS
  public static void bfs( int i, int j ){
    q = new LinkedList<Pii>();

    m[i][j] = cnt;
    q.add( new Pii(i,j) );

    while( !q.isEmpty() ){
      Pii v = q.remove();
      for ( int k = 0; k < 4; k++ ){
        int a = v.first + di[k];
        int b = v.second + dj[k];
        if ( m[a][b] == -1 ){
          m[a][b] = cnt;
          q.add( new Pii(a,b) );
        }
      }
    }
  }

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);

    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int M = Integer.parseInt(tokenizer.nextToken());
    int N = Integer.parseInt(tokenizer.nextToken());

    m = new int[M+2][N+2];
    for( int i = 0; i < M+2; i++ )
      for( int j = 0; j < N+2; j++ )
        m[i][j] = 0;

    for( int i = 1; i <= M; i++ ){
      line = in.readLine();
      tokenizer = new StringTokenizer(line," ");

      for( int j = 1; j <= N; j++ ){
        int t = Integer.parseInt(tokenizer.nextToken());
        if ( t == 1 ) m[i][j] = -1;
      }
    }

    cnt = 0;

    for( int i = 1; i <= M; i++ )
      for( int j = 1; j <= N; j++ )
        if ( m[i][j] == -1 ){
          cnt++;
          bfs( i, j );
        }

    writer.println( cnt );
    writer.close();
  }
}
