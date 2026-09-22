#!/usr/bin/env python3

# le a entrada
N,I,F = [int(i) for i in input().split()]
v = [int(i) for i in input().split()]


# computa resposta
res = 0
for i in range(N):
    for j in range(i+1,N):
        soma = v[i] + v[j]
        if I <= soma and soma <= F:
            res += 1

# e imprime resultado
print(res)
