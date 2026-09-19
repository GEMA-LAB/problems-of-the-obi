#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int vals[4];

  for (int i = 0; i < 4; i++) scanf("%d", &vals[i]);

  sort(vals, vals+4);

  bool ok = false;

  for (int i = 0; i+2 < 4; i++)
    if (vals[i+2] < vals[i] + vals[i+1])
      ok = true;
  
  printf(ok ? "S\n" : "N\n");

  return 0;
}
