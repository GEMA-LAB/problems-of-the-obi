#!/usr/bin/env python3

# OBI2021
# Fase 3
# Ogro

n = int(input())

if n >= 5:
    print('I'*(5))
elif n > 0:
    print('I'*(n))
else:
    print('*')

n -= 5

if n > 0:
    print('I'*(n))
else:
    print('*')
