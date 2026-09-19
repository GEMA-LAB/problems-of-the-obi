#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n < 100) {
        printf("%d\n", n);
    } else {
        // double resultado = n + 15;
        printf("%d\n", n + 15);
    }

    return 0;
}