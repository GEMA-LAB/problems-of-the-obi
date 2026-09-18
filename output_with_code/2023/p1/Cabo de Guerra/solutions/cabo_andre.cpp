#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
  vector<int> v;
  int s = 0;
  for(int i = 0; i < 6; i++) {
    int p; scanf("%d", &p);
    s += p;
    v.push_back(p);
  }
  
  bool impasse = false;
  for(int i = 0; i < 6; i++)
    for(int j = i + 1; j < 6; j++)
      for(int k = j + 1; k < 6; k++)
        if(v[i] + v[j] + v[k] == (s/2))
          impasse = true;
  if(s % 2 == 1) impasse = false;
  
  if(impasse) printf("S");
  else printf("N");
}