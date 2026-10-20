
/*
  OBI 2025 - Fase 1
  Festa
*/
import java.util.*;

public class festa {
  public static int max( int a, int b ){
    if( a > b ) return a; 
    return b; 
  }  

  public static int min( int a, int b ){ 
    if( a < b ) return a; 
    return b;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int e = scanner.nextInt();
    int s = scanner.nextInt();
    int m = scanner.nextInt();

    int maior = max( e, max( s, m )); 
    int menor = min( e, min( s, m ));

    System.out.println(2*(maior - menor));
  }
}
