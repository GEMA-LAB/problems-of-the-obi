#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110;
int marc[MAXN];
int main() {
  int r, n;
  scanf("%d %d", &r, &n);
  vector<pair<int, int> > frutas;
  for(int i = 1; i <= n; i++) {
    int t, p; scanf("%d %d", &t, &p);
    frutas.push_back({p, t});
  }
  sort(frutas.begin(), frutas.end());
  int resp = 0;
  for(int i = 0; i < frutas.size(); i++) {
    int p = frutas[i].first;
    int t = frutas[i].second;
    if(marc[t] == 0 && p <= r) {
      resp++;
      marc[t] = 1;
      r -= p;
    }
  }
  printf("%d\n", resp);
}