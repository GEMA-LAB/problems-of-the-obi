var K;
scanf("%d", "K");

var dp = new Array(K+1);

var MOD = 1000000007;
var pot2 = 1;
dp[1] = 1;
for (var i = 2; i <= K; i++) {
    if(i % 2 == 0)
        pot2 = (2*pot2) % MOD;
    dp[i] = (dp[i-1] + 2*pot2 - 1) % MOD;
    if(dp[i] < 0)
        dp[i] = (dp[i] + MOD) % MOD;
}

printf("%d\n", dp[K]);