#!/usr/bin/env python3

n, k = [int(x) for x in input().split()]

a = [int(x) for x in input().split()]

c = []

ans = 0

for i in range(n):
    for j in range(len(c)):
        if a[c[j]] == a[i]:
            c.pop(j)
            break
    c.append(i)
    if len(c) > k:
        c.pop(0)
    if len(c) == k:
        ans += c[0] + 1

print(ans)
