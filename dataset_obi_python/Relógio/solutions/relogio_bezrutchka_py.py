#!/usr/bin/env python3

hrs = int(input())
minu = int(input())
secs = int(input())
t = int(input())

secs += t
minu += (secs // 60)
secs %= 60
hrs += (minu // 60)
minu %= 60
hrs %= 24

print(hrs)
print(minu)
print(secs)
