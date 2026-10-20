import java.util.Scanner;

public class remove_greedy {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    scanner.close();
    int resp = 0;
    while (n > 0) {
      int x = n;
      int maxDigit = 0;
      while (x > 0) {
        int digit = x % 10;
        maxDigit = Math.max(maxDigit, digit);
        x /= 10;
      }
      n -= maxDigit;
      resp++;
    }
    System.out.println(resp);
  }
}
