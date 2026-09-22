#!/usr/bin/env python3

# 	Matheus Leal V
#   OBI 2019 - Fase 03 - Coleção
#	Complexidade O(N + M)

n, m = map(int, input().split())
 
n = int(n)
m = int(m)

lista = [ [] for x in range(n)] 
mark = [ 0 for x in range(n)] 

for i in range(0, n):
	lista.append([])

for i in range(0, m):
	a, b = map(int, input().split())
	a = int(a)
	b = int(b)
	a -= 1
	b -= 1
	lista[a].append(b)
	lista[b].append(a)

for i in range(n - 1, -1, -1):
	can = 1
	for x in lista[i]:
		if(mark[x]):
			can = 0

	if(can):
		mark[i] = 1

resposta = []
tam = 0
for i in range(0, n):
	if(mark[i]):
		resposta.append(i)
		tam += 1

print(tam)

for i in range(0, tam):
	if(i == tam - 1):
		print(resposta[i] + 1)
	else:
		print(resposta[i] + 1, end=' ')