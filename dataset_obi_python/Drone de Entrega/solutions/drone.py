#!/usr/bin/env python3

A = int(input())
B = int(input())
C = int(input())
H = int(input())
L = int(input())

resposta = "N"

if ( A <= H and B <= L  ): resposta = "S"
if ( A <= L and B <= H  ): resposta = "S"
if ( A <= H and C <= L  ): resposta = "S"
if ( A <= L and C <= H  ): resposta = "S"
if ( B <= H and C <= L  ): resposta = "S"
if ( B <= L and C <= H  ): resposta = "S"

print(resposta)
