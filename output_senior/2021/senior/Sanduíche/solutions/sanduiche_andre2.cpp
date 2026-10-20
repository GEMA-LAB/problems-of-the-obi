#include <bits/stdc++.h>
//Mega-sanduíche solucao parcial com bitmask O(2ˆN * M)
const int MAXM = 1000;
int aresta[MAXM][2];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d %d", &aresta[i][0], &aresta[i][1]);
        aresta[i][0]--;
        aresta[i][1]--;
    }
    int resp = 0;
    for(int mask = 1; mask < (1 << n); mask++) {
        int aux = 1;
        for(int i = 1; i <= m; i++) {
            int a = aresta[i][0], b = aresta[i][1];
            if((mask & (1 << a)) && (mask & (1 << b)))
                aux = 0;
        }
        resp += aux;
    }
    printf("%d\n", resp);
    return 0;
}
