#!/usr/bin/env python3

n = int(input())
arr = list(map(int, input().split()))

prev = -1
ptr = 0

while(ptr < n and arr[ptr] == 0):
    ptr += 1

ans = 0

while(ptr < n):
    curr = ptr
    ptr += 1

    while(ptr < n and arr[ptr] == 0):
        ptr += 1
    
    ans += (curr - prev) * (ptr - curr)
    
    prev = curr

print(ans)
    


