#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
    bool ok = false;
    for(int doses = 1; doses <= 50; doses++) {
        int leite = c - (d * doses);
        if(a <= leite && leite <= b) ok = true;
    }
    if(ok) printf("S\n");
    else printf("N\n");
}