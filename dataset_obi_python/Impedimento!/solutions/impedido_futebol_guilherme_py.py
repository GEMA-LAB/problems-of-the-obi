#!/usr/bin/env python2.7

[L, R, D] = [int(x) for x in raw_input().split()]

if ( R > 50 and L < R and R > D ): print "S"
else: print "N"
