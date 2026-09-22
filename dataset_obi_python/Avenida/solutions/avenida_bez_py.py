#!/usr/bin/env python3

d = int(input())

# divisão inteira para arredondar para baixo
ponto_antes = (d // 400) * 400
dist_antes = d - ponto_antes

ponto_depois = ponto_antes + 400
dist_depois = ponto_depois - d

print(min(dist_antes, dist_depois))
