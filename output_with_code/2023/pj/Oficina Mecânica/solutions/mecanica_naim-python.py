#! /usr/bin/env python3

from heapq import *

n,m = map(int, input().split())

t = list(map(int,input().split()))
f = list(map(int, input().split()))

t.sort(reverse=True)
f.sort()

q = []

for i in range(m):
    heappush(q, (0,i))
res=0
for tt in t:
    cur,id = heappop(q)
    res += tt * cur
    heappush(q, (cur + f[id] , id))

print(res)