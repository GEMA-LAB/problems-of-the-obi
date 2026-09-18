#!/usr/bin/env python3

n = int(input())
a = list(map(int, input().split()))

MAX_A = 10**5 + 1

freq = [0 for i in range(MAX_A)]

for x in a:
    freq[x] += 1

resp = 0
for i in range(MAX_A):
    resp += (freq[i] // 2)

print(resp)
