#include <cstdio>

int main() {
  int n, g, m;
  scanf("%d%d%d", &n, &g, &m);
  
  int num_pedacos = 8 * g + 6 * m;
  if (n >= num_pedacos) {
    printf("0\n");
  } else {
    printf("%d\n", num_pedacos - n);
  }
  return 0;
}
