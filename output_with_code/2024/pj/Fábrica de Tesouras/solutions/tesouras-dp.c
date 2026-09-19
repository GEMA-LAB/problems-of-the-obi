#include<stdio.h>

long long dp[50005];

int main(){
    long long MOD = 1000000007;
    int K;
    int s = scanf("%d", &K);

    long long pot2 = 1;
    dp[1] = 1;
    for(int i = 2; i <= K; i++){
        if(i % 2 == 0)
            pot2 = (2*pot2) % MOD;
        dp[i] = (dp[i-1] + 2*pot2 - 1) % MOD;
        if(dp[i] < 0)
            dp[i] = (dp[i] + MOD) % MOD;
    }
    printf("%llu\n", dp[K]);
    return 0;
}
