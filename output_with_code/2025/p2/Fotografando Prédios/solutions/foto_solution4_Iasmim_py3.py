#!/usr/bin/env python3

n = int(input())

a = [int(x) for x in input().split()]
f = [int(x) for x in input().split()]

a.append(int(1e9))

psum = [0]
s = [0]
last = [int(1e9)]
ans = [0 for _ in range(n)]

for i in range(n-1, -1, -1):
    p = len(psum) - 1 - f[i]
    ans[i] = -1 if (len(psum) - 1) < f[i] else psum[-1] - psum[p] - p*(s[-1]-s[p])
    while a[i] >= last[-1]:
        psum.pop()
        last.pop()
        s.pop()
    psum.append(psum[-1] + len(psum)*a[i])
    last.append(a[i])
    s.append(a[i]+s[-1])    

for x in ans:
    print(x, end=" ")
print()