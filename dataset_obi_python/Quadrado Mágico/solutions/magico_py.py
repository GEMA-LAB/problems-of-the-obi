#!/usr/bin/env python3

# OBI2022
# Problem magico

n = int(input())

m = []
for i in range(n):
    lin=[int(i) for i in input().split()]
    m.append(lin)


# find zero
zero = 0
ii = -1
jj = -1
for i in range(n):
    for j in range(n):
        if m[i][j] == 0:
            zero += 1
            ii,jj = i,j
            break;

# find value of sum
for i in range(n):
    zero = 0
    sum = 0
    for j in range(n):
        sum += m[i][j]
        if m[i][j] == 0:
            zero += 1
    if zero == 0:
        break;

# fix square
for i in range(n):
    zero = 0
    s = 0
    for j in range(n):
        s += m[i][j]
        if m[i][j] == 0:
            zero += 1
    if zero == 1:
        m[ii][jj] = sum - s
        break

print(m[ii][jj])
print(ii+1)
print(jj+1)
