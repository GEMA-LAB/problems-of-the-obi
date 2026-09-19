#! /usr/bin/env python3

n = len(input())
cadeia = input()

codigos = [] 
anterior = ''
repeticao = 1
for c in cadeia:
    if c == anterior:
        repeticao += 1
    else:
        if anterior != '':
            codigos.append(f'{repeticao} {anterior}')
        anterior = c
        repeticao = 1

codigos.append(f'{repeticao} {anterior}')

resposta = " ".join(codigos)
print(resposta)
