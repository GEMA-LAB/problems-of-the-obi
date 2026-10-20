/*
  OBI 2025 - Fase 1
  Cafeteria
*/
import java.util.*;

public class cafeteria {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int a = scanner.nextInt();
    int b = scanner.nextInt();
    int c = scanner.nextInt();
    int d = scanner.nextInt();
    boolean possivel = false;

    // testa todas as quantidades de doses
    for (int doses = 1; doses * d <= c; doses++) {
      int leite = c - doses * d;
      if (a <= leite && leite <= b) {
        possivel = true;
      }
    }

    if (possivel) {
      System.out.println("S");
    } else {
      System.out.println("N");
    }
  }
}
