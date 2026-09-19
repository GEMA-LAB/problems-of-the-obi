#!/usr/bin/env python3

j,p,v,e,d = [int(i) for i in input().split()]

if j == -1:
    tj1,tj2 = 0,101
else:
    tj1,tj2 = j,j+1
if p == -1:
    tp1,tp2 = 0,301
else:
    tp1,tp2 = p,p+1
if v == -1:
    tv1,tv2 = 0,101
else:
    tv1,tv2 = v,v+1
if e == -1:
    te1,te2 = 0,101
else:
    te1,te2 = e,e+1
if d == -1:
    td1,td2 = 0,101
else:
    td1,td2 = d,d+1

for tj in range(tj1,tj2):
    for tp in range(tp1,tp2):
        for tv in range(tv1,tv2):
            for te in range(te1,te2):
                for td in range(td1,td2):
                    if tj == tv + te + td and tp == 3*tv + te:
                        print(tj,tp,tv,te,td)

