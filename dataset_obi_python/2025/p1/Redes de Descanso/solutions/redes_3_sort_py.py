#!/usr/bin/env python3

n = int(input())
a = list(map(int, input().split()))

a.sort()
resp = 0
cnt = 1

for i in range(1, n):
    if a[i] == a[i - 1]:
        cnt += 1
    else:
        resp += (cnt // 2)
        cnt = 1
resp += (cnt // 2)

print(resp)
