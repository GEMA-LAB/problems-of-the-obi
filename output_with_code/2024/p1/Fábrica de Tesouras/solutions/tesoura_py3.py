#!/usr/bin/env python3

K = int(input())

dp = [int(0) for i in range(K+1)]

MOD = 1_000_000_007



pot2 = 1
dp[1] = 1
for i in range(2, K+1):
    if(i % 2 == 0):
        pot2 = (2*pot2) % MOD
    dp[i] = (dp[i-1] + 2*pot2 - 1) % MOD
    if(dp[i] < 0):
        dp[i] = (dp[i] + MOD) % MOD
print(dp[K])