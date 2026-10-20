#!/usr/bin/env python3

# OBI2021 - Fase 2
# Poligrama

def ordenaString(str):
    return ''.join(sorted(str))

n = int(input())
s = input().strip()

for k in range(1,n):
    if n % k == 0:
        a = ordenaString(s[0:k])
        ok = True
        for i in range(k,n,k):
            b = ordenaString(s[i:i+k])
            if a != b:
                ok = False
                break
        if ok:
            print(s[0:k])
            break

if not ok:
    print("*");
