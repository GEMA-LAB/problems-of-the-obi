#!/usr/bin/env python3

n = int(input())
a = list(map(int, input().split()))

freq = {}

for x in a:
    if x in freq:
        freq[x] += 1
    else:
        freq[x] = 1

resp = 0
for i in freq:
    resp += (freq[i] // 2)

print(resp)
