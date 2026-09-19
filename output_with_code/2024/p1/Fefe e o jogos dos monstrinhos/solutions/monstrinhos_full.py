#!/usr/bin/env python3
N = int(input())
F = int(input())

poder_m = [0] * N
poder_f = [0] * F
bonus_f = [0] * F

derrotado_m = [False] * N

for i in range(N):
    poder_m[i] = int(input())
for i in range(F):
    poder_f[i] = int(input())
for i in range(F):
    bonus_f[i] = int(input())

for i in range(N):
    for j in range(i, N):
        if(poder_m[i] > poder_m[j]):
            poder_m[i], poder_m[j] = poder_m[j], poder_m[i]

for i in range(F):
    for j in range(i, F):
        if(poder_f[i] > poder_f[j]):
            poder_f[i], poder_f[j] = poder_f[j], poder_f[i]
            bonus_f[i], bonus_f[j] = bonus_f[j], bonus_f[i]

resposta = 0

for i in range(F):
    for j in range(N):
        if(poder_f[i] < poder_m[j]):
            break
        if(bonus_f[i] == 0):
            break
        if(derrotado_m[j]):
            continue
        if(poder_f[i] > poder_m[j]):
            resposta += 1
            derrotado_m[j] = True
            bonus_f[i] -= 1
     
print(resposta)