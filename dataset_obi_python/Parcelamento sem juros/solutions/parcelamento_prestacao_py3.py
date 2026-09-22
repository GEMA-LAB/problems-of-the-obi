#!/usr/bin/env python3
# OBI-2019, prestacao

V = int(input())
P = int(input())

quociente = V//P;
resto = V%P;

for i in range(resto):
  print( quociente+1 )

for i in range(P-resto):
  print( quociente )
  