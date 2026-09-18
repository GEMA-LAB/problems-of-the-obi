// OBI-2020, escher

import java.util.*;
import java.io.*;
import java.lang.*;

public class escher_java {

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
  
    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int N = Integer.parseInt(tokenizer.nextToken());

    int A[] = new int[N+1];

    line = in.readLine();
    tokenizer = new StringTokenizer(line," ");
    for( int i = 1; i <= N; i++ )
      A[i] = Integer.parseInt(tokenizer.nextToken());

    boolean escher = true;
    int H = A[1]+A[N];

    for( int i = 1; i <= N; i++ )
      if ( A[i]+A[N-i+1] != H )
        escher = false;

    if ( escher ) writer.println( "S" );
    else writer.println( "N" );

    writer.close();
  }
}
