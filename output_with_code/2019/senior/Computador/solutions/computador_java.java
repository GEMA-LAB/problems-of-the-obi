// OBI-2019, computador

import java.util.*;
import java.io.*;
import java.lang.*;

public class computador_java {

  public static final int MAXN = 200001;
  public static final int MAX = 262144; // 2^18 > MAXN

  public static int MEIO( int i, int f ){ return ((i)+(((f)-(i)+1)/2)-1); }
  public static int ESQ( int i ){ return (2*(i)); }
  public static int DIR( int i ){ return (2*(i)+1); }

  public static class Segment {
    public Long F,T,Fcnt,Tcnt;
    public int i, f;
  }

  public static ArrayList<Segment> t;  // Segment tree

  public static int N,M;

  public static void init( int k, int i, int f ){
    t.get(k).i = i; t.get(k).f = f;
    t.get(k).F = t.get(k).T = 0L;
    t.get(k).Fcnt = t.get(k).Tcnt = 0L;
    if ( i > N ) return;
    if ( i != f ){
      init( ESQ(k), i, MEIO(i,f) );
      init( DIR(k), MEIO(i,f)+1, f );
    }
  }

  // range update
  public static void update( int k, Long v, boolean dir_frente, int l, int r ){

    // estritamente fora, sem recursao
    if ( t.get(k).i > r || t.get(k).f < l ) return;

    // estritamento dentro, sem recursao
    if ( t.get(k).i >= l && t.get(k).f <= r ){
      if ( dir_frente ){
        t.get(k).F += v-Long.valueOf(t.get(k).i-l);
        t.get(k).Fcnt++;
      } else {
        t.get(k).T += v-Long.valueOf(r-t.get(k).f);
        t.get(k).Tcnt++;
      }
      return;
    }

    // recursao, nem dentro, nem fora
    update( ESQ(k), v, dir_frente, l, r );
    update( DIR(k), v, dir_frente, l, r );
  }

  // point query
  public static Long query( int k, int p ){
    
    // calcula a contribuicao do segmento k
    Long aux = t.get(k).F-((Long.valueOf(p-t.get(k).i))*t.get(k).Fcnt) +
              t.get(k).T-((Long.valueOf(t.get(k).f-p))*t.get(k).Tcnt);
    
    if ( t.get(k).i == t.get(k).f ) // t.get(k).i == p, sem recursao
      return aux;
    else
      if ( p <= t.get(ESQ(k)).f ) // ESQ
        return aux + query( ESQ(k), p );
      else // DIR
        return aux + query( DIR(k), p );
  }

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);

    String line = in.readLine();
    StringTokenizer tokenizer = new StringTokenizer(line," ");
    N = Integer.parseInt(tokenizer.nextToken());
    M = Integer.parseInt(tokenizer.nextToken());

    int pw = 1; while( pw < N ) pw *= 2;

    t = new ArrayList<Segment>();
    for ( int i = 0; i < 2*MAX+1; i++ ) t.add( new Segment() );

    // inicializa segtree
    init( 1, 1, pw );
    /////////////////////

    int o,i,v;

    while ( M-- > 0 ){
      line = in.readLine();
      tokenizer = new StringTokenizer(line," ");
      o = Integer.parseInt(tokenizer.nextToken());

      switch( o ){
      case 3:
        i = Integer.parseInt(tokenizer.nextToken());
        writer.println( query( 1, i ) );
        break;
      case 1:
        i = Integer.parseInt(tokenizer.nextToken());
        v = Integer.parseInt(tokenizer.nextToken());
        update( 1, Long.valueOf(v), true, i, Math.min(i+v-1,N) );
        break;
      case 2:
        i = Integer.parseInt(tokenizer.nextToken());
        v = Integer.parseInt(tokenizer.nextToken());
        update( 1, Long.valueOf(v), false, Math.max(i-v+1,0), i );
      }
    }

    writer.close();
  }
}