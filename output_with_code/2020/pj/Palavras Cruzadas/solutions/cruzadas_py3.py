#!/usr/bin/env python3

# OBI2020
# palavras cruzadas

h = input()
v = input()

indice_h, indice_v = -1, -1
ok = True
for i in range(len(h)-1,-1,-1):
    for j in range(len(v)-1,-1,-1):
        if h[i] == v[j]:
            indice_h = i+1
            indice_v = j+1
            ok = False
            break
    if not ok:
        break

print(indice_h,indice_v)
