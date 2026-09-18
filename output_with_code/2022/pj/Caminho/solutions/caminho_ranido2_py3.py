#!/usr/bin/env python3

n = int(input())

primeiro_valor = int(input())
anterior = primeiro_valor
max_tamanho = 0
tamanho = 0

tamanho_primeiro = 0  # tamanho do trecho escuro consecutivo iniciando no primeiro poste
primeiro = True       # verdadeiro enquanto o trecho consecutivo inicia no primeiro poste

for i in range(1,n):
    corrente = int(input())
    if anterior + corrente < 1000:
        tamanho += 1
        if tamanho > max_tamanho:
            max_tamanho = tamanho
        if primeiro:
            tamanho_primeiro = max_tamanho
    else:
        primeiro = False
        tamanho = 0
    anterior = corrente

# fecha o círculo verificando o último com o primeiro_valor
if anterior + primeiro_valor < 1000:
    tamanho += 1
    if tamanho_primeiro > 0:
        tamanho += tamanho_primeiro
    if tamanho > max_tamanho:
        max_tamanho = tamanho

if max_tamanho > n:
    max_tamanho = n

print(max_tamanho)
