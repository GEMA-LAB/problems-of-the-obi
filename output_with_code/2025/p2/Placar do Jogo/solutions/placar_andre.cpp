#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<pair<int, int>> gols;
    int p; scanf("%d", &p);
    for(int i = 1; i <= p; i++) {
        int t; scanf("%d", &t);
        gols.push_back({t, 1});
    }
    int c; scanf("%d", &c);
    for(int i = 1; i <= c; i++) {
        int t; scanf("%d", &t);
        gols.push_back({t, 2});
    }
    sort(gols.begin(), gols.end());
    int placar[] = {0, 0, 0};
    printf("%d %d\n", placar[1], placar[2]);
    for(int i = 0; i < gols.size(); i++) {
        placar[gols[i].second]++;
        printf("%d %d\n", placar[1], placar[2]);
    }
}