#!/usr/bin/env python3

n = int(input())

resp = 0

for i in range(0,n):
	a, b = map(int, input().split())

	if a == 1:
		resp += 1
	elif b == 0:
		resp += 1

print(resp)
