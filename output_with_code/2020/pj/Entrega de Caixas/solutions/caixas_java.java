// OBI-2020, caixas

import java.util.*;
import java.io.*;
import java.lang.*;

public class caixas_java {

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
  
    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int A = Integer.parseInt(tokenizer.nextToken());

    line = in.readLine();
    tokenizer = new StringTokenizer(line," ");
    int B = Integer.parseInt(tokenizer.nextToken());

    line = in.readLine();
    tokenizer = new StringTokenizer(line," ");
    int C = Integer.parseInt(tokenizer.nextToken());

    if ( A == B ) {
      if ( B == C ) { 
        writer.println( 3 );
      } else {
        if ( A+B < C ) writer.println( 1 );
        else writer.println( 2 );
      }
    } else {
      if ( B < C ) {
        writer.println( 1 );
      } else {
        writer.println( 2 );
      }
    }

    writer.close();
  }
}
