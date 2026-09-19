#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
long long int a[MAXN];
int main() {
    int n; scanf("%d", &n);
    set<int> uns;
    uns.insert(0); uns.insert(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if(a[i] == 1) uns.insert(i);
    }
    long long int resp = 0;
    for(int i = 1; i <= n; i++)
        if(a[i] == 1) {
            auto it = uns.find(i);
            it--;
            long long int esq = *it;
            it++; it++;
            long long int dir = *it;
            resp += (i - esq) * (dir - 1 - i + 1);
        }
    printf("%lld\n", resp);
}