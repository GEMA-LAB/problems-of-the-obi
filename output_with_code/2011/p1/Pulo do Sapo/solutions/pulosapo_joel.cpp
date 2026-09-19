#include <cstdio>

const int MAXM = 110;

int N, M;
int P[MAXM], D[MAXM];

// valor absoluto
int abs(int a)
{
    return a < 0 ? -a : a;
}

int main()
{

    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &P[i], &D[i]);
    }

    for (int i = 1; i <= N; ++i) {
        bool pode_existir_sapo = false;
        for (int j = 0; j < M; ++j) {
            if (abs(P[j] - i) % D[j] == 0) { // se é divisível
                pode_existir_sapo = true;
            }
        }
        puts(pode_existir_sapo ? "1" : "0");
    }

    return 0;
}
