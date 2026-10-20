#!/usr/bin/env python3

from bisect import bisect_left

def main():
    n = int(input())

    v = list(map(int, input().split()))
    v.sort()

    resp = 0

    for i in range(n):
        for j in range(i + 1, n):
            soma = v[i] + v[j]
            ultimo_bom = bisect_left(v, soma) - 1
            if ultimo_bom > j:
                resp += ultimo_bom - j

    print(resp)

if __name__ == "__main__":
    main()
