#!/usr/bin/env python3
# encoding: utf-8
import sys
from functools import cmp_to_key
from itertools import accumulate

MOD = int(1e9 + 7)
INFL = int(4e18 + 25)
INF = int(1e9 + 42)
EPS = 1e-7
MAXN = int(1e6 + 1)

class Effect:
    def __init__(self, a=0, b=0):
        self.a = a
        self.b = b

    def __mul__(self, o):
        return Effect((self.a * o.a) % MOD, (self.b * o.a + o.b) % MOD)

    def apply(self, x):
        return (self.a * x + self.b) 

    def __lt__(self, o):
        return self.b * (o.a - 1) > o.b * (self.a - 1)

    def __sub__(self, o):
        return Effect(self.a - o.a, self.b - o.b)

    def cross(self, o):
        return self.a * o.b - self.b * o.a

    def __str__(self):
        return "({},{})".format(self.a, self.b)

def power(effect, exp):
    ret = Effect(1, 0)
    while exp:
        if exp & 1:
            ret = ret * effect
        effect = effect * effect
        exp >>= 1
    return ret

def main():
    # input = sys.stdin.read
    # data = input().split()
    idx = 0
    
    n, m, k = map(int,input().split())

    feit = [Effect() for _ in range(n)]
    esp = [Effect() for _ in range(m)]

    inn = list(map(int,input().split()))

    for i in range(n):
        feit[i].a = inn[i]

    inn = list(map(int,input().split()))

    for i in range(n):
        feit[i].b = inn[i]

    inn = list(map(int,input().split()))

    for i in range(m):
        esp[i].a = inn[i]

    inn = list(map(int,input().split()))

    for i in range(m):
        esp[i].b = inn[i]

    feit.sort(key=lambda x: (x.a, x.b))

    pareto = []
    for effect in feit:
        while pareto and pareto[-1].b <= effect.b:
            pareto.pop()
        pareto.append(effect)

    hull = []


    def check(eff):
        k = len(hull)
        return (eff - hull[k - 2]).cross(hull[k - 1] - hull[k - 2]) <= 0

    for effect in pareto:
        while len(hull) >= 2 and check(effect):
            hull.pop()
        hull.append(effect)

    feit = hull
    n =  len(feit)

    # print("hull_py:")
    # for i in hull:
    #     print(i)

    esp.sort()

    resp2 = Effect(1, 0)
    for e in esp:
        resp2 = resp2 * e

    best = Effect(0, 0)

    for effect in feit:
        if effect.a > best.a:
            best = effect
        if effect.a >= best.a and effect.b >= best.b:
            best = effect

    q = int(input())

    results = []

    # print("best = {}".format(best))

    queries = list(map(int,input().split()))
    for qi in range(q):
        x = queries[qi]

        resp1 = x
        bigyoshi = False

        if best.a == 1:
            resp1 = (x + k * best.b) % MOD
        else:
            for i in range(k):
                if bigyoshi:
                    resp1 = power(best, k - i).apply(resp1) % MOD
                    break
                else:
                    ini, fim = 0, n - 1
                    while ini != fim:
                        m = (ini + fim) // 2
                        if feit[m].apply(resp1) >= feit[m + 1].apply(resp1):
                            fim = m
                        else:
                            ini = m + 1
                    resp1 = feit[ini].apply(resp1)

                    # for i in feit:
                    #     print(i.apply(resp1), end=' ')
                    # print(" => {}".format(ini) )
                    if resp1 >= MOD:
                        resp1 %= MOD
                        bigyoshi = True

        results.append(resp2.apply(resp1) % MOD)

    sys.stdout.write('\n'.join(map(str, results)) + '\n')

if __name__ == "__main__":
    main()
