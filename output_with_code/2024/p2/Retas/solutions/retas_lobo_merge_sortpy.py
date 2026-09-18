#!/usr/bin/env python3

# Variável global para armazenar o número de inversões
ans = 0

# Função Merge Sort para contar inversões
def mergesort(v):
    global ans
    if len(v) == 1:
        return v

    mid = len(v) // 2
    vl = mergesort(v[:mid])  # Subvetor esquerdo
    vr = mergesort(v[mid:])  # Subvetor direito

    v_sorted = []
    l = r = 0

    # Realiza o merge dos dois subvetores ordenados
    while l < len(vl) and r < len(vr):
        if vl[l] < vr[r]:
            v_sorted.append(vl[l])
            l += 1
        else:
            v_sorted.append(vr[r])
            r += 1
            # Conta inversões, que é o número de elementos restantes em vl
            ans += len(vl) - l

    # Adiciona os elementos restantes de vl e vr
    v_sorted.extend(vl[l:])
    v_sorted.extend(vr[r:])

    return v_sorted

# Entrada de dados
ans = 0  # Zera a contagem de inversões
n, x1, x2 = map(int, input().split())

p = []
for _ in range(n):
    a, b = map(int, input().split())
    p.append((a * x1 + b, a * x2 + b))

# Ordena p com base na primeira coordenada e, em caso de empate, pela segunda coordenada de forma decrescente
p.sort(key=lambda x: (x[0], -x[1]))

# Cria o vetor v com as segundas coordenadas de p
v = [x[1] for x in p]

# Aplica Merge Sort e conta as inversões
mergesort(v)

# Imprime o número de inversões
print(ans)

