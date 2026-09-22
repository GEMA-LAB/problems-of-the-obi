#!/usr/bin/env python3

def check_old(plate):
  if len(plate) != 8:
    return False
  for i in range(8):
    if i < 3 and (plate[i] > 'Z' or plate[i] < 'A'):
      return False
    if i == 3 and plate[i] != '-':
      return False
    if i > 3 and (plate[i] > '9' or plate[i] < '0'):
      return False
  return True

def check_new(plate):
  if len(plate) != 7:
    return False
  for i in range(7):
    if (i < 3 or i == 4) and (plate[i] > 'Z' or plate[i] < 'A'):
      return False
    if (i > 3 and i != 4) and (plate[i] > '9' or plate[i] < '0'):
      return False
  return True

plate = input()
if check_old(plate):
  print(1)
elif check_new(plate):
  print(2)
else:
  print(0)
