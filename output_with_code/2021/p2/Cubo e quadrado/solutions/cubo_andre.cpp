#include <bits/stdc++.h>
using namespace std;
const int MAX = 100000010;
int marc[MAX];
int main() {
    int a, b; scanf("%d %d", &a, &b);
    for(int i = 1; (i * i) < MAX; i++) marc[(i * i)]++;
    for(int i = 1; (i * i * i) < MAX; i++) marc[(i * i * i)]++;
    int resp = 0;
    for(int i = a; i <= b; i++) if(marc[i] == 2) resp++;
    printf("%d\n", resp);
    return 0;
}
