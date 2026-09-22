#!/usr/bin/env python3

x = int(input())

while True:
    t = int(input())
    if t > x:
        print('menor')
    elif t < x:
        print('maior')
    else:
        print('correto')
        break
