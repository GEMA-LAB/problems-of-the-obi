#!/usr/bin/env python3
import sys

MAXN = 100010
poderes = [[] for _ in range(MAXN)]
resp = [[] for _ in range(MAXN)]
ativo = [[] for _ in range(MAXN)]
indice = [[] for _ in range(MAXN)]

class Celula:
    def __init__(self, linha, coluna, poder):
        self.linha = linha
        self.coluna = coluna
        self.poder = poder

def cmp(celula):
    return celula.poder

pai = [0] * MAXN
soma = [0] * MAXN
componente = [[] for _ in range(MAXN)]

def find(v):
    if pai[v] == v:
        return v
    pai[v] = find(pai[v])  # Compressão de caminho
    return pai[v]

def une(a, b):
    a = find(a)
    b = find(b)

    if a == b:
        return

    if len(componente[a]) > len(componente[b]):
        a, b = b, a

    componente[b].extend(componente[a])
    pai[a] = b
    soma[b] += soma[a]
    componente[a].clear()

dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

def main():
    # Ler n e m da primeira linha
    n, m = map(int, sys.stdin.readline().strip().split())
    celulas = []
    id_counter = 0

    # Ler os poderes da matriz
    for i in range(n):
        row = list(map(int, sys.stdin.readline().strip().split()))
        for j in range(m):
            p = row[j]
            poderes[i].append(p)

            nova = Celula(i, j, p)
            celulas.append(nova)

            id_counter += 1
            indice[i].append(id_counter)
            ativo[i].append(0)
            resp[i].append(0)

    # Ordena as células com base no poder
    celulas.sort(key=cmp)

    for i in range(len(celulas)):
        l = celulas[i].linha
        c = celulas[i].coluna
        p = celulas[i].poder

        ativo[l][c] = 1
        id = indice[l][c] - 1  # Ajuste para índice zero
        componente[id].append(celulas[i])
        pai[id] = id
        soma[id] = p

        for k in range(4):
            vizl = l + dx[k]
            vizc = c + dy[k]
            if vizl < 0 or vizl >= n or vizc < 0 or vizc >= m:
                continue
            if ativo[vizl][vizc] == 0:
                continue

            vizid = indice[vizl][vizc] - 1  # Ajuste para índice zero
            vizpai = find(vizid)

            if p <= soma[vizpai]:
                une(id, vizpai)
            else:
                for t in range(len(componente[vizpai])):
                    lcel = componente[vizpai][t].linha
                    ccel = componente[vizpai][t].coluna
                    resp[lcel][ccel] = soma[vizpai]
                componente[vizpai].clear()
                une(vizpai, id)

    llast = celulas[-1].linha
    clast = celulas[-1].coluna
    idlast = indice[llast][clast] - 1  # Ajuste para índice zero
    pailast = find(idlast)

    for t in range(len(componente[pailast])):
        lcel = componente[pailast][t].linha
        ccel = componente[pailast][t].coluna
        resp[lcel][ccel] = soma[pailast]

    # Imprime a saída em uma única linha por linha
    for i in range(n):
        print(" ".join(map(str, resp[i])))

if __name__ == "__main__":
    main()
