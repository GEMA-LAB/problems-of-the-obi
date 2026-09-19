#!/usr/bin/env python3

dp_maxi_ways = []
dp_mini_ways = []
dp_mini_len = []

MAXN = 100006

MOD = 1000000007

def init():
	for i in range(MAXN):
		dp_mini_len.append(-1)
		dp_mini_ways.append(-1)
		dp_maxi_ways.append(-1)

def solve(x):
	if x == 0:
		return (1, 1, 0)

	global dp_maxi_ways, dp_mini_ways, dp_mini_len

	if dp_maxi_ways[x] != -1:
		return (dp_maxi_ways[x], dp_mini_ways[x], dp_mini_len[x])

	sm = 1
	r = 1

	maxi_ways = 0
	mini_ways = 0
	mini_len = 1000000000

	while sm <= x:
		curr_maxi_ways, curr_mini_ways, curr_mini_len = solve(x - sm)

		maxi_ways += curr_maxi_ways

		if curr_mini_len < mini_len:
			mini_len = curr_mini_len
			mini_ways = curr_mini_ways
		elif curr_mini_len == mini_len:
			mini_ways += curr_mini_ways

		mini_ways %= MOD
		maxi_ways %= MOD

		r += 1
		sm += r*r

	dp_maxi_ways[x] = maxi_ways
	dp_mini_ways[x] = mini_ways
	dp_mini_len[x] = mini_len + 1

	return (maxi_ways, mini_ways, mini_len + 1)

def main():
	init()

	raw = input().split()
	g = int(raw[0])
	m = int(raw[1])

	for i in range(g+1):
		solve(i)

	maxi_ways, mini_ways, mini_len = solve(g)

	if m == 1:
		print(int(maxi_ways))
	else:
		print(int(mini_ways))

if __name__ == "__main__":
	main()