#! /usr/bin/env python3

def solve():
    cubos = [int(x) for x in input().split()]

    total = sum(cubos)

    if total % 3 != 0:
        return "N"

    qtd = total // 3
    cubos.sort()

    if cubos[-1] != qtd:
        return "N"

    cubos.pop()

    for i in range(len(cubos)):
        for j in range(i + 1, len(cubos)):
            segundo_andar = cubos[i] + cubos[j]
            if segundo_andar == qtd:
                return "S"
    return "N"


print(solve())
