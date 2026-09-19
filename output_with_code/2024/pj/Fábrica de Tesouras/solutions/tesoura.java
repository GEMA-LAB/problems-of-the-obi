import java.util.Scanner;
import java.util.Arrays;

public class tesoura {
    public static void main(String[] args) {
        long MOD = 1000000007;

        Scanner sc = new Scanner(System.in);
        int K = sc.nextInt();
        long dp[] = new long[K+1];

        long pot2 = 1;
        dp[1] = 1;

        for(int i = 2; i <= K; i++){
            if(i % 2 == 0)
                pot2 = (pot2*2) % MOD;
            dp[i] = (dp[i-1] + pot2*2 - 1) % MOD;
            if(dp[i] < 0)
                dp[i] = (dp[i] + MOD) % MOD;
        }

        System.out.println(dp[K]);
    }
}