#include <stdio.h>

int main() {
    long long int x, y, z, n;

    scanf("%lld %lld %lld %lld", &x, &y, &z, &n);

    printf("%lld\n", (x + y + z) % n);
}
