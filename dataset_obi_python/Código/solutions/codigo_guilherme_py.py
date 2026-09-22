#!/usr/bin/env python2.7

N = int(raw_input())
s = [int(x) for x in raw_input().split()]

res = 0
for i in xrange((N+1)-3):
    if ( s[i:i+3] == [1,0,0] ):
        res += 1

print res
