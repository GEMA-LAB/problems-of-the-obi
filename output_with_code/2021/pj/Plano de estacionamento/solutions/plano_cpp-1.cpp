// OBI2021 - Fase 3
// Plano de ação

#include <bits/stdc++.h>

using namespace std;

int main(void) {

  int n, m, total=0;

  scanf("%d%d",&n,&m);
  int vagas[n+1];

  memset(vagas, 0, sizeof(vagas));

  bool ok = true;
  for (int i=0; i<m && ok; i++) {
    int plano;
  
    scanf("%d", &plano);

    while (plano > 0 && vagas[plano] > 0) {
      int t = vagas[plano];
      vagas[plano]++;
      plano -=  t;
    }
    if (plano <= 0)
      ok = false;
    else {
      vagas[plano] = 1;
      total++;
    }
  }

  printf("%d\n", total);
  return 0;
}
