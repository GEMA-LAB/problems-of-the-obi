#!/usr/bin/env python3
X = int(input())

ans = 0

if X < 6:
	if X == 1:
		ans = 1
	elif X == 2:
		ans = 2
	elif X == 3:
		ans = 4
	elif X == 4:
		ans = 5
	elif X == 5:
		ans = 7
else:
	ans = 13
	while X > 6:
		ans += 6
		X -= 1

print(ans)