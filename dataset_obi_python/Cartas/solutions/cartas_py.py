#!/usr/bin/env python2.7

A = int(raw_input())
B = int(raw_input())
C = int(raw_input())

if ( A == B ):
    falta = C
elif ( A == C ):
    falta = B
else:
    falta = A

print falta
