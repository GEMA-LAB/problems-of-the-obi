#!/usr/bin/env python3

import heapq

def solve(array):
	queue = [] # min-heap
	ans = 0
	for i,val in enumerate(array):
		valor = val + i
		heapq.heappush(queue, valor)
		while queue and queue[0] < i + 1:
			heapq.heappop(queue)
		ans = max(ans, len(queue))
	return ans

N = int(input())
array = list(map(int, input().split()))
print(solve(array))
