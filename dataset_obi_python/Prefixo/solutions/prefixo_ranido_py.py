#! /usr/bin/env python3

n = int(input()) # não usado
palavra1 = input()

n = int(input()) # não usado
palavra2 = input()

resp = 0
i = 0
while True:
    if i == len(palavra1) or i == len(palavra2):
        break
    if palavra1[i] == palavra2[i]:
        resp += 1
        i += 1
    else:
        break

print(resp)
