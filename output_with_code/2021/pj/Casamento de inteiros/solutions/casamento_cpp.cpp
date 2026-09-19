// OBI2021 - Fase 3
// Casamento

#include <bits/stdc++.h>
using namespace std;

string a, b;

int main(void) {
  cin >> a >> b;

  // ajusta os tamanhos adicionando zeros à esquerda
  while (a.size() < b.size())
    a = "0" + a;
  while (b.size() < a.size())
    b = "0" + b;

  string na, nb;
  for (int i=0; i<a.size(); i++){
    if (a[i] == b[i]) {
      na += a[i];
      nb += b[i];
    }
    else if (a[i] < b[i])
      nb += b[i];
    else
      na +=a[i];
  }

  int res1, res2;
  if (na.size() == 0)
    res1 = -1;
  else
    res1 = stoi(na);
  
  if (nb.size() == 0)
    res2 = -1;
  else
    res2 = stoi(nb);
  
  if (res2 > res1)
    printf("%d %d\n",res1,res2);
  else
    printf("%d %d\n",res2,res1);
  
  return 0;
}

    
