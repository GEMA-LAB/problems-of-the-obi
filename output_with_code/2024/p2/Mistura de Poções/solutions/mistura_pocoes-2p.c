#include <stdio.h>

#define MAX_N (100001)

int a[MAX_N];
int f[MAX_N];
int T;

int main() {
    int n, k;
    T = scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        T = scanf("%d", &a[i]);
    }

    long long ans = 0;

    int p = 1;

    int d = 0;

    for (int i = 1; i <= n; ++i) {
        d += (f[a[i]]++ == 0);

        while (d >= k) {
            d -= (--f[a[p]] == 0);
            ++p;
        }

        ans += p - 1;
    }

    printf("%lld\n", ans);

    return 0;
}
