#include <bits/stdc++.h>
using namespace std;

long long sum(long long ini, long long fim) {
    return (ini + fim) * (fim - ini + 1) / 2LL;
}
int main() {
    int p; scanf("%d", &p);
    for(int i = 1; i <= p; i++) {
        long long int l, a, b; scanf("%lld %lld %lld", &l, &a, &b);
        if(sum(a, b) < l) printf("%lld\n", b - a + 1);
        else {
            //busca binaria pra encontrar o primeiro cuja soma dá maior ou igual a l
            long long ini = a, fim = b;
            while(ini < fim) {
                long long m = (ini + fim)/2;
                if(sum(a, m) >= l) fim = m;
                else ini = m + 1;
            }
            printf("%lld\n", ini - a + 1);
        }
    }
}