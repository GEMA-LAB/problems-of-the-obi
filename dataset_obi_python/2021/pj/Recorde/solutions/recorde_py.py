#!/usr/bin/env python3

# OBI2021 - Fase 2
# Recorde

r = int(input())
m = int(input())
l = int(input())

if r < m:
    print('RM')
else:
    print('*')

if r < l:
    print('RO')
else:
    print('*')
