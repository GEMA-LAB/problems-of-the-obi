#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300010;
int a[MAXN], qtd[MAXN];
int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if(a[i] > 0) {
            qtd[i]++;
            if(i + a[i] <= n) qtd[i + a[i]]--;
        }
    }
    int resp = 0;
    for(int i = 1; i <= n; i++) {
        qtd[i] += qtd[i - 1];
        resp = max(resp, qtd[i]);
    }
    printf("%d\n", resp);
}