#include <stdio.h>

const int M = 1000 * 1000 * 1000 + 7;

signed main() {
    int n;
    int T = scanf("%d", &n);

    int a = 0, b = 0, c = 1;
    for (int i = 0; i < n; ++i) {
        long long x = (2ll * (a + b) + c);
        while (x >= M) x -= M;
        a = b;
        b = c;
        c = x;
    }
    printf("%d\n", c);

    return 0;
}
