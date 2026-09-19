/*
  OBI 2025 - Fase 1
  Cafe com Leite
*/
import java.util.*;

public class leite {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int a = scanner.nextInt();
    int b = scanner.nextInt();
    int c = scanner.nextInt();
    int d = scanner.nextInt();

    if (a <= c - d && c - d <= b) {
      System.out.println("S");
    } else {
      System.out.println("N");
    }
  }
}
