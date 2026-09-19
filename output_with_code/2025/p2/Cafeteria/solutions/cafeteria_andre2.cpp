#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
    if((c - a)%d != 0 && ((c - a)/d) == ((c - b)/d)) printf("N\n");
    else printf("S\n");
}