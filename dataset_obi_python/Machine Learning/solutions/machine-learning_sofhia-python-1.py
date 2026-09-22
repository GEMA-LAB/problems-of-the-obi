#!/usr/bin/env python3

N = int(input())

dicionario = {}
cont = {}

for _ in range(N):
    line = input().split()
    S = line[0]
    k = int(line[1])
    
    cont[S] = 0
    for i in range(2, len(line)):
        word = line[i]
        dicionario[word] = S

X = int(input())
maior_valor = 0
topico_do_artigo = ""

artigo = input().split()

for word in artigo:

    if word not in dicionario:
        continue

    cont[dicionario[word]] += 1

    if cont[dicionario[word]] > maior_valor or (cont[dicionario[word]] == maior_valor and topico_do_artigo > dicionario[word]):
        maior_valor = cont[dicionario[word]]
        topico_do_artigo = dicionario[word]

print(topico_do_artigo)