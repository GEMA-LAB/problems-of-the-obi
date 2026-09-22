#!/usr/bin/env python3

valor = int(input())
acougue = int(input())
farmacia = int(input())
padaria = int(input())

menor = min(acougue, farmacia, padaria)
maior = max(acougue, farmacia, padaria)

if acougue == maior:
    meio = max(farmacia, padaria)
elif farmacia == maior:
    meio = max(acougue, padaria)
else:
    meio = max(acougue,farmacia)

# print("menor", menor)
# print("meio", meio)
# print("maior", maior)

if maior + meio + menor <= valor:
    resp = 3
elif menor + meio <= valor:
    resp = 2
elif menor <= valor:
    resp = 1
else:
    resp = 0

print(resp)
