#!/usr/bin/env python3.9
# OBI2021
# Fase 3
# Dona Minhoca

def dfs(x, id, p=-1):
    global L, dis
    for i in L[x]:
        if i == p or dis[id][i] > 0:
            continue
        dis[id][i] = 1 + dis[id][x]
        dfs(i,id,x)


def cont(x, d, p):
    global L
    if d == 0:
        return 1
    r = 0
    for i in L[x]:
        if i != p:
            r += cont(i,d-1,x)    
    return r

n = int(input())
L = [[] for i in range(n)]
dis = [[0 for i in range(n)] for i in range(3)]

for i in range(n-1):
    x = input().split()
    a = int(x[0]) - 1
    b = int(x[1]) - 1
    L[a].append(b)
    L[b].append(a)
    
dfs(0,0)

A = 0;
for i in range(n):
    if dis[0][i] > dis[0][A]:
        A = i
dfs(A,1)
    

B = 0
for i in range(n):
    if dis[1][i] > dis[1][B]:
        B = i

dfs(B,2)
#for i in range(3):
#    print('dis[i]',dis[i])

cent = []

for i in range(n):
    if (dis[1][i] + dis[2][i] == dis[1][B]) and (abs(dis[1][i]-dis[2][i]) <= 1):
        cent.append(i)
        #print("cent",i)

#print('cent',cent)

diam = dis[1][B]

ans = 0

if len(cent) == 1:
    sum = 0
    for i in L[cent[0]]:
        u = cont(i,round(diam/2)-1,cent[0])
        #print("u",u);
        ans -= round((u*u-u)/2)
        #print("ans",ans);
        sum += u
        
    ans += round((sum*sum-sum)/2);
    print(diam+1)
    print(ans)
else:
    A = cont(cent[0],diam//2,cent[1])
    B = cont(cent[1],diam//2,cent[0])
    print(diam+1)
    print(A*B)

