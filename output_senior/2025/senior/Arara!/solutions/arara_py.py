#! /usr/bin/env python3

araras, gaiolas = map(int, input().split())
qtd = (gaiolas + 4) // 5 

if qtd >= araras:
	print("S")
else:
	print("N")

 
