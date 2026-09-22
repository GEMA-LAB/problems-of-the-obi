#!/usr/bin/env python3

n, k = [int(x) for x in input().split()]

a = [int(x) for x in input().split()]

f = [0] * (n + 1)

ans = 0

d = 0
p = 0

for i in range(n):
    if f[a[i]] == 0: d += 1
    f[a[i]] += 1

    while d >= k:
        f[a[p]] -= 1
        if f[a[p]] == 0: d -= 1
        p += 1
    
    ans += p

print(ans)
