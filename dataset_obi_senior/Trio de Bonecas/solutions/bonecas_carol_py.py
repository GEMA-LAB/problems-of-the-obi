#! /usr/bin/env python3

INF = 1e18 + 10

[n, k] = map(int, input().split())
t = [0] + [int(x) for x in input().split()]
t.sort()

dp = [[INF] * (k + 1) for i in range(n + 1)]
dp[0][0] = 0

for i in range(1, n + 1):
    for j in range(k + 1):
        ans = dp[i - 1][j]
        used = (k - j) * 3
        if (n - i) > used and i > 1 and j > 0:
            cost = t[i] - t[i - 1]
            cost = cost * cost
            ans = min([ans, cost + dp[i - 2][j - 1]])
        dp[i][j] = ans

print(dp[n][k])
