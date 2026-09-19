#!/usr/bin/env python3

import string
letras = string.ascii_letters.lower()

n,m = [int(i) for i in input().split()]



for i in range(1, m+1):
    x = i
    while x > 0:
        print(letras[x % 10], end='')
        x //= 10
    print(end=' ')
print()
