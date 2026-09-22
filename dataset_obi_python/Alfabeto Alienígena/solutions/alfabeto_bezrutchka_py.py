#!/usr/bin/env python3

[k, n] = [int(x) for x in input().split()]
alphabet = input()
message = input()

answer = "S"
for c in message:
  if not c in alphabet:
    answer = "N"
    break
print(answer)
