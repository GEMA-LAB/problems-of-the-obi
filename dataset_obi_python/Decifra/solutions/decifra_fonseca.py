#!/usr/bin/env python2.7
import string

s1 = raw_input()
s2 = raw_input()
print s2.translate(string.maketrans(string.ascii_lowercase, s1))