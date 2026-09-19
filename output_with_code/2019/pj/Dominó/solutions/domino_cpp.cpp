// Guilherme A. Pinto, domino, OBI-2019

#include <iostream>
using namespace std;

int main(){
  int N;

  cin >> N;

  int numero_de_pecas = ((N+1)*(N+2))/2;
  
  cout << numero_de_pecas << endl;
  
  return 0;
}
