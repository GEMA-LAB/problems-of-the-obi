/*
  OBI 2025 - Fase 1
  Pizzaria
*/
import java.util.*;

public class pizzaria {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int g = scanner.nextInt();
    int p = scanner.nextInt();
    int amigos = g * 8 + p * 4 - 2;
    System.out.println(amigos);
  }
}
