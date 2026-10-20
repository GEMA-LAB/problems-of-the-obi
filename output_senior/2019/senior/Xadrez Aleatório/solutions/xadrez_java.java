// OBI-2019, xadrez

import java.util.*;
import java.io.*;
import java.lang.*;

public class xadrez_java {

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);

    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int N = Integer.parseInt(tokenizer.nextToken());
    int T = Integer.parseInt(tokenizer.nextToken());

    if ( T == 0 ) writer.println( N );
    if ( T == 1 ) writer.println( N*(N-1) ); // combinação de N dois a dois, vezes dois (por quê?)
    if ( T == 2 ) writer.println( (N*(N-1)*(N-2))/6 ); // combinação de N três a três (por quê?)

    writer.close();
  }
}
