#!/usr/bin/env python3

a,b=[int(i) for i in input().split()]
if a < b:
    print(2*a-b)
else:
    print(2*b-a)
