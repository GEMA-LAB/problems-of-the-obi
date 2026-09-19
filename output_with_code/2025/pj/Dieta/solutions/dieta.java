/*
  OBI 2025 - Fase 1
  Dieta
*/
import java.util.*;

public class dieta {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int n = scanner.nextInt();
    int m = scanner.nextInt();

    int calorias = 0;

    for( int i = 0; i < n; i++ ){
        int p = scanner.nextInt();
        int g = scanner.nextInt();
        int c = scanner.nextInt();
        calorias += 4*p + 9*g + 4*c;
    }

    System.out.println(m - calorias);
  }
}
