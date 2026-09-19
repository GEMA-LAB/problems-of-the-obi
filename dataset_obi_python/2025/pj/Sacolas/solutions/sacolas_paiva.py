#!/usr/bin/env python3

n, s = map(int, input().split())

soma = 0
res = 0
l = list(map(int, input().split()))

for i in range(0, n):
	x = l[i]
	if soma + x > s:  
		soma = x
		res+=1
	else:
		soma += x

print(res+1)