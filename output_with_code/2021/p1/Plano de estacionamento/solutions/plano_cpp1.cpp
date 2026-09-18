#include <cstdio>

using namespace std;

const int MAXN = 110;

int x, n;
int m[MAXN];

int main() {

    scanf("%d%d", &x, &n);

    int soma = 0;
    for(int i=0; i<n; i++){
        scanf("%d", &m[i]);
        soma += m[i];
    }

    printf("%d\n", x * (n + 1) - soma);
    
    return 0;
}
