#!/usr/bin/env python2.7
 ############################################################################
 # Arthur Pratti Dadalto
 # OBI 2016
 ############################################################################

tab = {"norte" : 0, "leste" : 1, "sul" : 2, "oeste" :3}
s = raw_input().split()
print 90 * min(abs(tab[s[0]] - tab[s[1]]), 4 - abs(tab[s[0]] - tab[s[1]]))