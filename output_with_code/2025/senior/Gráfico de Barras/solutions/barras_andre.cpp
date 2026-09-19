#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    int x[n], h = 0;
    for(int j = 0; j < n; j++) {
        scanf("%d", &x[j]);
        h = max(h, x[j]);
    }
    int mat[h][n];
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < h; i++) {
            if(i < h - x[j]) mat[i][j] = 0;
            else mat[i][j] = 1;
        }
    }
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}