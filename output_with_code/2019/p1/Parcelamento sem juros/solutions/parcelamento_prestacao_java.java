// OBI-2019, prestacao

import java.util.*;
import java.io.*;
import java.lang.*;

public class prestacao_java {

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);

    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    int V = Integer.parseInt(tokenizer.nextToken());    

    line = in.readLine();
    tokenizer = new StringTokenizer(line," ");
    int P = Integer.parseInt(tokenizer.nextToken());

    int quociente = V/P;
    int resto = V%P;

    for( int i = 0; i < resto; i++ )
      writer.println( quociente+1 );

    for( int i = 0; i < P-resto; i++ )
      writer.println( quociente );

    writer.close();
  }
}
