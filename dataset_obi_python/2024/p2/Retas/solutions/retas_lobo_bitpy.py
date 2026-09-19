#!/usr/bin/env python3
import bisect

# Função para atualizar a árvore de Fenwick (BIT)
def upd(bit, n, pos, val):
    while pos <= n:
        bit[pos] += val
        pos += pos & -pos

# Função para calcular a soma na árvore de Fenwick (BIT)
def soma(bit, pos):
    val = 0
    while pos > 0:
        val += bit[pos]
        pos -= pos & -pos
    return val

# Entrada de dados
n, x1, x2 = map(int, input().split())

p = []
cc = []
for _ in range(n):
    a, b = map(int, input().split())
    p.append((a * x1 + b, a * x2 + b))
    cc.append(a * x2 + b)

# Ordena e remove duplicatas
cc = sorted(list(set(cc)))
p.sort(key=lambda x: (x[0], -x[1]))

# Inicializa a BIT (árvore de Fenwick)
bit = [0] * (n + 1)  # BIT de tamanho n + 1 (usando índices a partir de 1)
ans = 0

for i in range(n):
    # Encontra o índice usando busca binária (bisect_right)
    x = bisect.bisect_right(cc, p[i][1])
    ans += i - soma(bit, x-1)  # Soma dos elementos menores que o atual
    upd(bit, n, x, 1)  # Atualiza a BIT com o novo valor

# Saída do resultado
print(ans)

