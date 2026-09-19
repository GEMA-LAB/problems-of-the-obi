#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int p[MAXN];
int main() {
    int n, s; scanf("%d %d", &n, &s);
    int resp = 1;
    int soma = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        if(soma + p[i] > s) {
            resp++;
            soma = p[i];
        } else {
            soma += p[i];
        }
    }
    printf("%d\n", resp);
}