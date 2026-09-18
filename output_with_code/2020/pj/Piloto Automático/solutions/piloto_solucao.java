// OBI-2020, piloto

import java.util.*;
import java.io.*;
import java.lang.*;

public class solucao {

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

    int distAB = B-A;
    int distBC = C-B;

    if ( distAB < distBC ){
      writer.println( 1 );
    } else {
      if ( distAB > distBC ){
        writer.println( -1 );
      } else {
        writer.println( 0 );
      }
    }

    writer.close();
  }
}
