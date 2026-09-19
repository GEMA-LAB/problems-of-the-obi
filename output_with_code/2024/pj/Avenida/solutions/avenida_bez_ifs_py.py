#!/usr/bin/env python3

d = int(input())

if d <= 200:
  resp = d
elif d <= 400:
  resp = 400 - d
elif d <= 600:
  resp = d - 400
elif d <= 800:
  resp = 800 - d
elif d <= 1000:
  resp = d - 800
elif d <= 1200:
  resp = 1200 - d
elif d <= 1400:
  resp = d - 1200
elif d <= 1600:
  resp = 1600 - d
elif d <= 1800:
  resp = d - 1600
else:
  resp = 2000 - d

print(resp)
