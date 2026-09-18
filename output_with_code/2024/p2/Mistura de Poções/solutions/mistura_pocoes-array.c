#include <stdio.h>

int a[100001];
int T;

int main() {
    int n, k;
    T = scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        T = scanf("%d", &a[i]);
    }

    long long ans = 0;

    int c[4], sz = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < sz; ++j) {
            if (a[c[j]] == a[i]) {
                --sz;
                for (int p = j; p < sz; ++p) {
                    c[p] = c[p + 1];
                }
                break;
            }
        }
        c[sz++] = i;
        if (sz > k) {
            --sz;
            for (int p = 0; p < sz; ++p) {
                c[p] = c[p + 1];
            }
        }
        if (sz == k) {
            ans += c[0];
        }
    }

    printf("%lld\n", ans);

    return 0;
}
