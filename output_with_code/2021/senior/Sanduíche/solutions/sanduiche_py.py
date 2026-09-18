#!/usr/bin/env python3

def calc(x):
    global n, usado
    if x == n+1:
        return 1
    ret = calc(x+1)

    ok = True
    for v in proibido[x]:
        if usado[v]:
            ok = False
            break

    if ok:
        usado[x] = True
        ret += calc(x+1)
        usado[x] = False

    return ret



n, m = [int(i) for i in input().split()]
usado = [False for i in range(n+1)]
proibido = [set() for i in range(n+1)]

for i in range(m):
    x, y = [int(i) for i in input().split()]
    proibido[x].add(y)
    proibido[y].add(x)

print(calc(1)-1)
