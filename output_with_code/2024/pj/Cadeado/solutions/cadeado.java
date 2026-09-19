/*
OBI 2024 - Fase 3
  Cadeado
  Solução em O(N) com iteração e análise de casos
*/

import java.util.*;

public class cadeado {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int n = scanner.nextInt();
    int s, c;
    int clicks = 0;
    for (int i = 0; i < n; i++) {
      s = scanner.nextInt();
      c = scanner.nextInt();
      if (s < c) {
        int hor = c - s;
        int anti_hor = 10 + s - c;
        clicks += Math.min(hor, anti_hor);
      } else {
        int anti_hor = s - c;
        int hor = 10 + c - s;
        clicks += Math.min(hor, anti_hor);
      }
    }
    
    System.out.println(clicks);
  }
}
