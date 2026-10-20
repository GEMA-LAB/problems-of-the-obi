#!/usr/bin/env python3

n = int(input())

v = list(map(int, input().split()))
v.sort()

resp = 0
    
for i in range(n):
    l = 0
    for r in range(i - 1, 0, -1):
        while l < r and v[l] + v[r] <= v[i]:
            l += 1
        if l < r:
            resp += (r - l)

print(resp)
