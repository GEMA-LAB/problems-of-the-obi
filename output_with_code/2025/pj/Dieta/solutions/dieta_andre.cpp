#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; scanf("%d %d", &n, &m);
    int tot = 0;
    for(int i = 0; i < n; i++) {
        int p, g, c; scanf("%d %d %d", &p, &g, &c);
        tot += (4 * p) + (9 * g) + (4 * c);
    }
    printf("%d\n", m - tot);
}