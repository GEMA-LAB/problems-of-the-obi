// OBI2022

#include<bits/stdc++.h>

using namespace std;

int c, d, t;

int main (void) {
    scanf("%d%d%d", &c, &d, &t);

    double litros = (double) d / (double) c;
    double compra = litros - t;

    if (compra < 0)
	compra = 0;

    printf("%.1f\n", compra);

    return 0;
}
