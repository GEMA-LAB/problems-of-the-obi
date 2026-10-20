// OBI-2020, paciente

import java.util.*;
import java.io.*;
import java.lang.*;

public class solucao {

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
  
    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int N = Integer.parseInt(tokenizer.nextToken());
    int C = Integer.parseInt(tokenizer.nextToken());

    boolean z[] = new boolean[N+1];
    for( int i = 0; i <= N; i++ )
        z[i] = true;

    for( int c = 0; c < C; c++ ){
      line = in.readLine();
      tokenizer = new StringTokenizer(line," ");
      int P = Integer.parseInt(tokenizer.nextToken());
      int I = Integer.parseInt(tokenizer.nextToken());

      for( int i = 0; i < I; i++ ){
        int X = Integer.parseInt(tokenizer.nextToken());
        z[X] = false;
      }
    }

    for( int i = 1; i <= N; i++ )
      if ( z[i] )
        writer.println( i );

    writer.close();
  }
}
