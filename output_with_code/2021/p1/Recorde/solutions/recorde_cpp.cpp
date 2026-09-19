// OBI2021 - Fase 2
// Recorde

#include <cstdio>

using namespace std;


int r, m, l;

int main(void) {
  scanf("%d%d%d", &r, &m, &l);

  if (r < m)
    printf("RM\n");
  else
    printf("*\n");

  if (r < l)
    printf("RO\n");
  else
    printf("*\n");

  return 0;
}
