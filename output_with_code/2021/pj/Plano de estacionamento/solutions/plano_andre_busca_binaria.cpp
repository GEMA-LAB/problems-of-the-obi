#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000010;
int v[MAX], aux[MAX];
bool test(int t) {
    for(int i = 1; i <= t; i++) aux[i] = v[i];
    sort(aux + 1, aux + t + 1);
    //colocar aux[i] na vaga i
    for(int i = 1; i <= t; i++) if(aux[i] < i) return false;
    return true;
}
int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++) scanf("%d", &v[i]);
    int ini = 1, fim = m;
    while(ini < fim) {
        int mid = (ini + fim)/2;
        if(fim == ini + 1) mid = fim;
        if(test(mid)) ini = mid;
        else fim = mid - 1;
    }
    printf("%d\n", ini);
    return 0;
}
