#!/usr/bin/env python3

[n, k] = [int(x) for x in input().split()]
vals = [int(x) for x in input().split()]
vals.sort()
print(vals[n - k])
