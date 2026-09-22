#!/usr/bin/env python3

def main():
  n = int(input())
  resp = 0
  while n > 0:
    x = n
    max_digit = 0
    while x > 0:
      digit = x % 10
      max_digit = max(max_digit, digit)
      x //= 10
    n -= max_digit
    resp += 1
  print(resp)

if __name__ == "__main__":
  main()
