#!/usr/bin/env python3
raw = input().split()
n = int(raw[0])
m = int(raw[1])
k = int(raw[2])

if n//k < m:
  print(-1)
  exit()

rating = []

txt = input().split()

for i in range(n):
  rating.append(int(txt[i]))

maxi = 0
for i in range(n):
  maxi = max(maxi, rating[i])

l_rating = 0
r_rating = maxi + 1

while l_rating < r_rating:
  p_rating = (l_rating + r_rating) // 2

  def solve():
    groups = 0
    cnt_less = 0
    for i in range(n):
      if rating[i] < p_rating:
        cnt_less += 1
      if cnt_less == m:
        cnt_less = 0
        groups += 1
    
    return groups >= k
  
  if not solve():
    l_rating = p_rating+1
  else:
    r_rating = p_rating

print(l_rating)
