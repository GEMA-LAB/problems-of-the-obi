// OBI2021 - Fase 2
// Lista palíndroma

#include <cstdio>

using namespace std;

typedef long long llint; 

const int MAXN = 1e6 + 10;

int n;
llint lista[MAXN];

int main(void) {

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) 
    scanf("%lld", &lista[i]);

  int sol = 0, p_esq = 0, p_dir = n - 1;

  while (p_esq < p_dir) {
    
    if (lista[p_esq] == lista[p_dir]) {
      ++p_esq; --p_dir;
      continue;
    }

    if (lista[p_esq] < lista[p_dir]) {
      lista[p_esq + 1] += lista[p_esq];
      ++p_esq;
    } else {
      lista[p_dir - 1] += lista[p_dir];
      --p_dir;
    }

    ++sol;

  }

  printf("%d\n", sol);

  return 0;

}
