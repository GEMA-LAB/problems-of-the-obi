#!/usr/bin/env python3

x, y, z, n = [int(i) for i in input().split()]

print((x + y + z) % n)