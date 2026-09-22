#!/usr/bin/env python3

"""
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - define o representante de cada grupo de amigos
      como o menor ID no grupo
    - usa um set para ver se algum representante
      aparece mais de uma vez em uma entrevista

   [Tecnicamente o set de Python tem pior caso O(N) por
    operação, mas na maioria dos casos (e nesse problema)
    é efetivamente O(1) por operação. Também é possível
    usar um vetor de marcação para garantir O(1) por
    operação, mas na prática é mais lento (ambas
    implementações recebem 100 pontos).]
"""

from sys import stdin

def main():
    n = int(stdin.readline())
    tabela = [stdin.readline() for _ in range(n)]
    
    # representante de um candidato == o amigo dele de menor ID;
    # dois candidatos são amigos se e somente se possuem
    # o mesmo representante
    representante = []
    for i in range(n):
        representante.append(i)
        for j in range(i):
            if tabela[i][j] == '1' and representante[i] == i:
                representante[i] = j

    e = int(stdin.readline())
    for _ in range(e):
        linha = list(map(int, stdin.readline().split()))
        possui_amigos = False
        representantes_na_entrevista = set()
        for candidato in linha[1:]:
            candidato -= 1  # estamos indexando do zero
            if representante[candidato] in representantes_na_entrevista:
                possui_amigos = True
            else:
                representantes_na_entrevista.add(representante[candidato])
        if possui_amigos:
            print("S")
        else:
            print("N")


if __name__ == "__main__":
    main()
