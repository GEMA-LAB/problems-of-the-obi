#!/usr/bin/env python3

maxn = 10100

n = int(input())
m = int(input())

ans = [i  for i in range(min(n,maxn))]

v = []
for i in range(m):
    v.append(int(input()))
    

for i in range(m-1,-1,-1):
    for j in range(min(n,maxn)):
        if ans[j] >= n:
            break
        ans[j] += ans[j] // (v[i]-1)

for i in range(min(10000,n)):
    if ans[i] >= n:
        break
    print(ans[i]+1)
