#include <cstdio>

int main() {
  int n, m, p, ult = 0;
  bool consegue = true;

  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", &p);
    consegue = consegue && ((p-ult) <= m);
    ult = p;
  }
  consegue = consegue && ((42195-ult) <= m);
  printf("%c\n", consegue ? 'S' : 'N');
  
  return 0;
}
