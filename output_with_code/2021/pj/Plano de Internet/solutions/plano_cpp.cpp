#include <cstdio>

using namespace std;

int x, n;
int m;

int main(void) {

    scanf("%d%d", &x, &n);

    int soma = 0;
    for(int i=0; i<n; i++){
        scanf("%d", &m);
        soma += m;
    }

    printf("%d\n", x * (n + 1) - soma);
    
    return 0;
}
