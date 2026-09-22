#!/usr/bin/env python3

"""
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - modela os grupos de amigos como componentes conexas
      de um grafo. Faz DFS para identificar os grupos de amigos
    - usa um set para ver se alguma componente aparece
      mais de uma vez em uma entrevista

   [Tecnicamente o set de Python tem pior caso O(N) por
    operação, mas na maioria dos casos (e nesse problema)
    é efetivamente O(1) por operação. Também é possível
    usar um vetor de marcação para garantir O(1) por
    operação, mas na prática é mais lento (ambas
    implementações recebem 100 pontos).]
"""

from sys import stdin
from sys import setrecursionlimit

setrecursionlimit(5000)

def main():
    n = int(stdin.readline())
    tabela = [stdin.readline() for _ in range(n)]

    componente = [None for _ in range(n)]
    def dfs(v, c):
        componente[v] = c
        for w in range(n):
            if componente[w]:
                continue
            if tabela[v][w] == '1':
                dfs(w, c)
    
    comp_atual = 1
    for v in range(n):
        if not componente[v]:
            dfs(v, comp_atual)
            comp_atual += 1

    e = int(stdin.readline())
    for _ in range(e):
        linha = list(map(int, stdin.readline().split()))
        possui_amigos = False
        componentes_na_entrevista = set()
        for candidato in linha[1:]:
            candidato -= 1  # estamos indexando do zero
            if componente[candidato] in componentes_na_entrevista:
                possui_amigos = True
            else:
                componentes_na_entrevista.add(componente[candidato])
        if possui_amigos:
            print("S")
        else:
            print("N")


if __name__ == "__main__":
    main()
