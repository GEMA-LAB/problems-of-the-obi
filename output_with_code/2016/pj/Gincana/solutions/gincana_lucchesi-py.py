#!/usr/bin/env python
# coding: utf-8
# solução para o problema "turma"

import sys

def mdc(a, b):
  while b > 0:
    r = a % b
    a, b = b, r
  return a;

s = sys.stdin.read().split()
n = int(s.pop(0))
m = int(s.pop(0))
x = m;
while mdc(n, x) > 1: x -= 1
print x
