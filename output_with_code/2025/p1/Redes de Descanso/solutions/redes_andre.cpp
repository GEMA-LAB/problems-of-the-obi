#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int marc[MAXN];
int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        marc[a]++;
    }
    int resp = 0;
    for(int i = 1; i < MAXN; i++)
        resp += marc[i]/2;
    printf("%d\n", resp);
}