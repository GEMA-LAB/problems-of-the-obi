/*
  OBI 2025 - Fase 1
  Fila
*/
import java.util.*;

public class fila {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int n = scanner.nextInt();
    int maior = -1, resposta = 0;

    int v[] = new int[n];

    for( int i = 0; i < n; i++ ){
      v[i] = scanner.nextInt();
    }
    
    for( int i = n - 1; i >= 0; i-- ){
      if( v[i] <= maior ) resposta++; 
      else maior = v[i];
    }

    System.out.println(resposta);
  }
}
