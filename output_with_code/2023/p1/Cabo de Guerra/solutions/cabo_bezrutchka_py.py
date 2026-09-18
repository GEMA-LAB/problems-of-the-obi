#! /usr/bin/env python3

"""
 * OBI 2023 - Fase 3
 * Cabo de Guerra - Solução listando todos os casos
 * Mateus Bezrutchka
"""

a, b, c, d, e, f = [int(x) for x in input().split()]

achei = False

if a + b + c == d + e + f:
  achei = True
if a + b + d == c + e + f:
  achei = True
if a + b + e == c + d + f:
  achei = True
if a + b + f == c + d + e:
  achei = True
if a + c + d == b + e + f:
  achei = True
if a + c + e == b + d + f:
  achei = True
if a + c + f == b + d + e:
  achei = True
if a + d + e == b + c + f:
  achei = True
if a + d + f == b + c + e:
  achei = True
if a + e + f == b + c + d:
  achei = True

if achei:
  print("S")
else:
  print("N")

