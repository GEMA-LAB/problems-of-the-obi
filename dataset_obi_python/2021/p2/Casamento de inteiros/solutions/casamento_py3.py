#!/usr/bin/env python3

# OBI2021 - Fase 2
# Casamento

a = input()
b = input()

while len(a) < len(b):
    a = "0" + a
while len(b) < len(a):
    b = "0" + b

na = []
nb = []

for i in range(len(a)):
  na.append(a[i])
  nb.append(b[i])
  if a[i] < b[i]: na.pop()
  if b[i] < a[i]: nb.pop()



if len(na) == 0:
    res1 = -1
else:
    res1 = int("".join(na))

if len(nb) == 0:
    res2 = -1
else:
    res2 = int("".join(nb))

if res2 > res1:
    print(res1,res2)
else:
    print(res2,res1)
    
