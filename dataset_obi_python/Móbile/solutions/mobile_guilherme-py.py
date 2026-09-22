#!/usr/bin/env python2.7

A = int(raw_input())
B = int(raw_input())
C = int(raw_input())
D = int(raw_input())

if ( A == B+C+D and B+C == D and B == C ): resp = "S"
else: resp = "N"

print resp
