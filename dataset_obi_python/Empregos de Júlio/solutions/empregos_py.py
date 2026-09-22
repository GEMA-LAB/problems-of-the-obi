#!/usr/bin/env python3

# OBI 2025 - Fase 3
# Empregos

from heapq import *

n, k = map(int, input().split())

a = list(map(int, input().split()))
b = list(map(int, input().split()))

best_prefix = 0
answer = 0
best_suffix = [0]*(n + 1)
for i in range(n - 1, -1, -1):
    best_suffix[i] = best_suffix[i + 1] + max( a[i], 2*b[i] )
    answer += max( a[i], b[i] )

if( k == 0 ):
    print(best_suffix[0])
    exit(0)

k_smallest = []

for i in range(n):
    best_prefix += b[i]
    heappush( k_smallest, b[i] - a[i] )
    if i + 1 < k:
        continue
    
    if len(k_smallest) > k and k_smallest[0] <= 0:
        best_prefix -= heappop(k_smallest)
    
    answer = max( answer, best_prefix + best_suffix[i + 1])

print(answer)
