#!/usr/bin/env python2.7

tempos = []
for x in xrange(3):
	tempos.append( (int(raw_input()), x+1) )

tempos.sort()
for tempo, indice in tempos:
	print indice