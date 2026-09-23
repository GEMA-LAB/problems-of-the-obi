#!/usr/bin/env python3

import sys
import collections
sys.setrecursionlimit(200000)

MAXL = 21

n = 0
k = 0 
q = 0
g = []
m = []
memo = []
pro = []
niv = []
p = []
xor = []

def anc(i, j):
    return memo[i][j]

def lca(x, y):
    if niv[x] < niv[y]:
        x, y = y, x

    for i in range(MAXL, -1, -1):
        if niv[x] - 2 ** i >= niv[y]:
            x = anc(x, i)

    if x == y:
        return x

    for i in range(MAXL, -1, -1):
        if niv[x] - 2 ** i >= 0 and anc(x, i) != anc(y, i):
            x = anc(x, i)
            y = anc(y, i)

    return p[x]

def bfs(st):
    pro[st] = 1
    q = collections.deque([st])

    while len(q):
        v = q.popleft()

        for u in g[v]:
            if not pro[u]:
                pro[u] = 1

                xor[u] = xor[v] ^ m[u]
                niv[u] = niv[v] + 1
                p[u] = v

                q.append(u)

def count1s(x):
    s = str(bin(x))
    ans = 0
    for b in s:
        if b == '1':
            ans += 1
    return ans

if __name__ == "__main__":
    n, k = map(int, input().split())
    for _ in range(n + 1):
        m.append(0)
        pro.append(0)
        niv.append(0)
        p.append(0)
        xor.append(0)
        g.append([])
        l = []
        for _ in range(MAXL):
            l.append(-1)
        memo.append(l)


    for i in range(n - 1):
        x, y = map(int, input().split())
        g[x].append(y)
        g[y].append(x)

    for i in range(1, n + 1):
        if k == 0:
            continue
        b = list(map(int, input().split()))
        x = 0
        for j in range(k):
            x |= (2 ** j) * b[j]
        m[i] = x

    bfs(1)

    for i in range(1, n + 1):
        memo[i][0] = p[i]

    for j in range(1, MAXL):
        for i in range(1, n + 1):
            memo[i][j] = memo[memo[i][j - 1]][j - 1]

    q = int(input())
    for _ in range(q):
        x, y = map(int, input().split())
        z = lca(x, y)

        print(count1s(xor[x] ^ xor[y] ^ m[z]))
