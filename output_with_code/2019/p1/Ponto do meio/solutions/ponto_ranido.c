#include<stdio.h>

int main(void) {
  int n, i;
  unsigned long lado;

  scanf("%d",&n);
  lado = 2;
  for (int i = 0; i < n; i++) {
    lado += lado - 1;
  }
  printf("%ld\n", lado*lado);

  return 0;
}
