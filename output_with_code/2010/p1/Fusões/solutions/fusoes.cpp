#include <cstdio>

#define MAX 100100

int pai[MAX];

int N, K;

int find(int p) {
    return pai[p] == p ? p : pai[p] = find(pai[p]);
}

int main(void) {
    scanf("%d%d", &N, &K);

    for(int i = 0; i < N; ++i) {
        pai[i] = i;
    }

    for(int i = 0; i < K; ++i) {
        char c;
        int A, B;
        scanf(" %c %d %d", &c, &A, &B);
        A = find(A-1);
        B = find(B-1);
        if(c == 'F') {
            pai[A] = B;
        } else {
            printf("%s\n", A==B?"S":"N");
        }
    }
    
    return 0;
}
