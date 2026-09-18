import java.util.Scanner;

public class yvens_tabuleiro_good_java {
    private static final int M = 1000000007;
    private static final int MAXN = 100005;
    
    public static void main(String[] args) {
        long[] dp = new long[MAXN];
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 3;

        for (int i = 3; i < MAXN; i++) {
            dp[i] = (dp[i - 1] + 2 * dp[i - 2] + 2 * dp[i - 3]) % M;
        }

        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();

        System.out.println(dp[n]);
        scanner.close();
    }
}