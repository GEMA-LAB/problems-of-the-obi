#!/usr/bin/env python3

def main():
    n = int(input())

    a = list(map(int, input().split()))
    a.sort()

    resp = 0
    for i in range(n - 2):
        k = i + 2
        for j in range(i + 1, n - 1):
            k = max(k, j + 1)
            while k < n and a[i] + a[j] > a[k]:
                k += 1
            resp += (k - 1) - j

    print(resp)

if __name__ == "__main__":
    main()
