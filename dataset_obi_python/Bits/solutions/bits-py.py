#!/usr/bin/env python2.7

# Guilherme A. Pinto, OBI-2017, bits

MOD = 1000000007

[N, K] = [int(c) for c in raw_input().split()]

dp = [0]*(N+1)
pot2 = [0]*(N+1)

pot2[0] = 1
for i in range(1,N+1):
    pot2[i] = (pot2[i-1]*2)%MOD

for i in range(1,N+1):
    if ( i < K ):
        dp[i] = pot2[i]
    elif ( i == K ):
        dp[i] = pot2[i]-1
    else:
        dp[i] = 0
        for k in range(1,K+1):
            dp[i] = (dp[i]+dp[i-k])%MOD

print dp[N]
