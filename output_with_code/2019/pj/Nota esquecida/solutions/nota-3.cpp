// Guilherme A. Pinto, nota, OBI-2019

#include <bits/stdc++.h>
using namespace std;

// Solucao mais "sofisticada":
// dadas as condicoes, a area estritamente maior sera aquela que contiver
// estritamente o centro da nota original, o ponto (80,35). Portanto,
// Felix tera o maior pedaco se, e somente se, a orientacao do triangulo
// [(B,0),(T,70),(80,35)] for anti-horaria. De outra forma, se o produto
// cruzado: [(T,70)-(B,0)] X [(80,35)-(B,0)] for maior do que zero.

struct pt { // ponto (ou vetor)
  int x, y;
  pt(int x_, int y_): x(x_), y(y_) {}
  pt operator-(pt p) { return pt(x - p.x, y - p.y); } // subtracao vetorial
  int operator%(pt p) { return x*p.y - y*p.x; } // produto cruzado
};

int main(){
  int B,T;
  cin >> B >> T;
  
  int produto_cruzado = (pt(T,70) - pt(B,0)) % (pt(80,35) - pt(B,0));
  
  if ( produto_cruzado > 0 ) {
    cout << 1 << endl;
  } else {
    if ( produto_cruzado < 0 ) {
      cout << 2 << endl;
    } else {
      cout << 0 << endl;
    }
  }

  return 0;
}
