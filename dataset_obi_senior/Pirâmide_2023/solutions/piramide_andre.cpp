#include <bits/stdc++.h>
using namespace std;
int main() {
  vector<int> v;
  int s = 0;
  for(int i = 1; i <= 6; i++) {
    int p; scanf("%d", &p);
    s += p;
    v.push_back(p);
  }
  sort(v.begin(), v.end());
  
  bool cond0 = (s%3 == 0);
  bool cond1 = (v[5] == (s/3));
  bool cond2 = false;
  for(int i = 0; i < 5; i++)
    for(int j = i + 1; j < 5; j++)
      if(v[i] + v[j] == v[5])
        cond2 = true;
  
  if(cond0 && cond1 && cond2) printf("S");
  else printf("N");
}