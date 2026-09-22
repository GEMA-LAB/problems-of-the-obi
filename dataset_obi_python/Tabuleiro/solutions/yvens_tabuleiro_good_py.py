#!/usr/bin/env python3

M = 1000000007
MAXN = 100005
dp = [-1] * MAXN

dp[0] = 1
dp[1] = 1
dp[2] = 3

for i in range(3, MAXN):
    dp[i] = (dp[i - 1] + 2 * dp[i - 2] + 2 * dp[i - 3]) % M

n = int(input())

print(dp[n])