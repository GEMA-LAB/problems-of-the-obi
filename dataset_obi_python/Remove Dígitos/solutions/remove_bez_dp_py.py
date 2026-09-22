#!/usr/bin/env python3

def main():
  n = int(input())
  dp = [n + 1] * (n + 1)
  dp[0] = 0
  for i in range(1, n + 1):
    x = i
    while x > 0:
      digit = x % 10
      if digit > 0:
        dp[i] = min(dp[i], dp[i - digit] + 1)
      x //= 10
  print(dp[n])

if __name__ == "__main__":
  main()
