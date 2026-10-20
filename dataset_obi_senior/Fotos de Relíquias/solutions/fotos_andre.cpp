#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
long long int a[MAXN], esq[MAXN], dir[MAXN];
int main() {
    int n; scanf("%d", &n);
    int last = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        esq[i] = last;
        if(a[i] == 1) last = i;
    }
    last = n + 1;
    for(int i = n; i >= 1; i--) {
        dir[i] = last;
        if(a[i] == 1) last = i;
    }
    long long int resp = 0;
    for(int i = 1; i <= n; i++)
        if(a[i] == 1)
            resp += (i - esq[i]) * (dir[i] - 1 - i + 1);
    printf("%lld\n", resp);
}