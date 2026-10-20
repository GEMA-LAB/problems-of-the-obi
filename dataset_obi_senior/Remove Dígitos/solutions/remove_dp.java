import java.util.Scanner;

public class remove_dp {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = scanner.nextInt();
    scanner.close();
    int[] dp = new int[n + 1];
    for (int i = 0; i <= n; i++) {
      dp[i] = Integer.MAX_VALUE;
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
      int x = i;
      while (x > 0) {
        int digit = x % 10;
        if (digit > 0) {
          dp[i] = Math.min(dp[i], dp[i - digit] + 1);
        }
        x /= 10;
      }
    }
    System.out.println(dp[n]);
  }
}
