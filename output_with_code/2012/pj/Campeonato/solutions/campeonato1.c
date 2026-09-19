#include <stdio.h>

int main (int argc, char *noargs[]) {
  int vc, ec, sc, vf, ef, sf, pf, pc;
  char *res;
  scanf ("%d %d %d %d %d %d", &vc, &ec, &sc, &vf, &ef, &sf);
  pc = 3 * vc + ec;
  pf = 3 * vf + ef;
  if ((pc > pf) || ((pc == pf) && (sc > sf)))
    res = "C";
  else if ((pc < pf ) || ((pc == pf) && (sc < sf)))
    res = "F";
  else res = "=";
  printf ("%s\n", res);
  return 0;
}
