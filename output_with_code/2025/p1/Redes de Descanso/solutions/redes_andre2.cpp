#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    vector<int> v;
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        v.push_back(a);
    }
    sort(v.begin(), v.end());
    int resp = 0;
    for(int i = 1; i < n; i++)
        if(v[i] == v[i - 1]) {
            resp++;
            v[i] = -i;
        }
    printf("%d\n", resp);
}