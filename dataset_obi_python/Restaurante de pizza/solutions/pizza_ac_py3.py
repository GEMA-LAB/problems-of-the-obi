#!/usr/bin/env python3

a = int(input())
b = int(input())
r = int(input())
g = int(input())

ok = 1

if 2 * r > a:
	ok = 0

if 2 * r > b:
	ok = 0

if (360 % g) != 0:
	ok = 0

if ok == 0:
	print("N")
else:
	print("S")	
