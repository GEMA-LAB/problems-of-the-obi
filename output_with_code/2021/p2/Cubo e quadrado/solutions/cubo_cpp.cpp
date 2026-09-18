// OBI2021 - Fase 3
// Cubo e quadrado

#include <cstdio>
#include <cmath>

using namespace std;


int a, b, resp;

int main(void) {
  scanf("%d%d", &a, &b);
  
  int raiz_cubica = int(pow(a,1./3.));
  int cubo = raiz_cubica * raiz_cubica * raiz_cubica;
  if (cubo < a) {   // raiz_cubica foi truncada, pode ser menor do que a
    raiz_cubica++;
    cubo = raiz_cubica * raiz_cubica * raiz_cubica;
  }

  //procura por cubos entre a e b, verificando se é também um quadrado
  resp = 0;
  while (cubo <= b) {
    int raiz_quadrada = int(sqrt(cubo));
    int quadrado = raiz_quadrada * raiz_quadrada;
    if (quadrado == cubo) {
      resp++;
    }
    raiz_cubica++;
    cubo = raiz_cubica * raiz_cubica * raiz_cubica;
  }

  printf("%d\n",resp);
  return 0;
}
