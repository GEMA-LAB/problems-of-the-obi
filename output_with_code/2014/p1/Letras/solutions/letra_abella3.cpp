/* This solution is intentionally very input-format dependant. */

#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  char c = getchar();
  getchar();

  int c2;

  int nword = 0, nok = 0;

  bool lastok = false;
  while ((c2 = getchar()) != -1) {
    if (c2 == ' ' || c2 == '\n') {
      nword++;
      if (lastok) nok++;
      lastok = false;
    } else {
      if (c2 == c) lastok = true;
    }
  }

  printf("%.1f\n", 100.0 * nok / nword);

  return 0;
}
