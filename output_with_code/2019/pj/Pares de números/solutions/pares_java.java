// OBI-2019, pares

import java.util.*;
import java.io.*;
import java.lang.*;

public class pares_java {

  public static int[] v = new int[1000];

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);

    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int N = Integer.parseInt(tokenizer.nextToken());    
    int I = Integer.parseInt(tokenizer.nextToken());    
    int F = Integer.parseInt(tokenizer.nextToken());    

    line = in.readLine();
    tokenizer = new StringTokenizer(line," ");
    for( int i = 0; i < N; i++ )
      v[i] = Integer.parseInt(tokenizer.nextToken());

    int res = 0;

    for( int i = 0; i < N-1; i++ )
      for( int j = i+1; j < N; j++ ){
        int soma = v[i]+v[j];
        if ( I <= soma && soma <= F )
          res++;
      }

    writer.println( res );
    writer.close();
  }
}
