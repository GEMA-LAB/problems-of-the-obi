#! /usr/bin/env python3

def solve(f):
    soma = sum(f)
    
    if soma % 2 == 1:
        return 'N'
    
    soma = soma/2

    for i in range(1, len(f)):
        for j in range(i+1, len(f)):
            if (f[i] + f[j] + f[0]) == soma:
                return 'S'
    
    return 'N'

f = [int(x) for x in input().split()]
print(solve(f))
