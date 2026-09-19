#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAXN 50

using namespace std;

int linesum[MAXN], colsum[MAXN], M[MAXN][MAXN];

int main() {
  int n;

  cin >> n;

  for (int y = 0; y < n; y++) linesum[y] = 0;
  for (int x = 0; x < n; x++) colsum[x] = 0;

  for (int y = 0; y < n; y++)
    for (int x = 0; x < n; x++) {
      cin >> M[y][x];
      linesum[y] += M[y][x];
      colsum[x] += M[y][x];
    }

  int cy = -1, cx = -1;

  for (int y = 0; y < n; y++)
    if (linesum[y] != linesum[(y+1)%n] && linesum[y] != linesum[(y+2)%n])
      cy = y;
  for (int x = 0; x < n; x++)
    if (colsum[x] != colsum[(x+1)%n] && colsum[x] != colsum[(x+2)%n])
      cx = x;

  if (cy == -1 || cx == -1) {
    abort();
  }

  int newvalue = M[cy][cx];
  int oldvalue = newvalue - (linesum[cy] - linesum[(cy+1)%n]);

  cout << oldvalue << " " << newvalue << endl;

  return 0;
}
