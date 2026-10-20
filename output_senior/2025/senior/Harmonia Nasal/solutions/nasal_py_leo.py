#!/usr/bin/env python3
n, k = map(int,input().split())

a = list(map(int,input().split()))
b = list(map(int,input().split()))

resp = 0

add = []
k+=1
k = min(k,n)

for i in range(n):
    if(a[i] >= b[i]):
        resp+=a[i]-b[i]
        add.append(b[i])
    else:
        add.append(a[i])

add.sort(key = lambda x: -x)

for i in range(k):
    resp+=add[i]

print(resp)