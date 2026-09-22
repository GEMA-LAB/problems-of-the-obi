#!/usr/bin/env python3

N, Q = map(int, input().split())
queries = [list(map(int, input().split())) for _ in range(Q)]

prv = [0] * (N+1)
par = [-1] * (N+1)
sz = [1] * (N+1)
d = [[0, 0] for _ in range(N+1)]

def find(a):
	while par[a] >= 0:
		if par[par[a]] >= 0:
			par[a] = par[par[a]]
		a = par[a]
	return a

def merge(a, b, cost):
	a, b = find(a), find(b)
	par[b] = a
	x = d[a][0] + d[b][0] + cost * sz[b]
	y = d[a][1] + d[b][1] + sz[b] * (d[a][0] + sz[a] * cost) + sz[a] * d[b][0]
	sz[a] += sz[b]
	d[a] = x, y

for i in range(Q):
	a = queries[i]
	if a[0] == 1:
		prv[a[1]] = i
		prv[a[2]] = i

for query in queries:
	if query[0] == 1:
		a, b, cost = query[1], query[2], query[3]
		if prv[a] < prv[b]:
			a, b = b, a
		merge(a, b, cost)
	if query[0] == 2:
		print(d[find(query[1])][1])
	